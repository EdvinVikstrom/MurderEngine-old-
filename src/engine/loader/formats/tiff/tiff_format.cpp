#include "tiff_format.hpp"
#include "tifflzw_decompressor.hpp"

static me::format::tiff_field_type getTIFFFieldType(uint16_t type)
{
  if (type == 1) return me::format::tiff_field_type::TIFF_FT_BYTE;
  else if (type == 2) return me::format::tiff_field_type::TIFF_FT_ASCII;
  else if (type == 3) return me::format::tiff_field_type::TIFF_FT_SHORT;
  else if (type == 4) return me::format::tiff_field_type::TIFF_FT_LONG;
  else if (type == 5) return me::format::tiff_field_type::TIFF_FT_RATIONAL;
  else if (type == 6) return me::format::tiff_field_type::TIFF_FT_SBYTE;
  else if (type == 7) return me::format::tiff_field_type::TIFF_FT_UNDEFINED;
  else if (type == 8) return me::format::tiff_field_type::TIFF_FT_SSHORT;
  else if (type == 9) return me::format::tiff_field_type::TIFF_FT_SLONG;
  else if (type == 10) return me::format::tiff_field_type::TIFF_FT_SRATIONAL;
  else if (type == 11) return me::format::tiff_field_type::TIFF_FT_FLOAT;
  else if (type == 12) return me::format::tiff_field_type::TIFF_FT_DOUBLE;
  return me::format::tiff_field_type::TIFF_FT_UNDEFINED;
}

static me::metadata::TagType fromTIFFFieldType(uint16_t type)
{
  if (type == 1) return me::metadata::TagType::MTT_UINT8;
  else if (type == 2) return me::metadata::TagType::MTT_STRING;
  else if (type == 3) return me::metadata::TagType::MTT_UINT16;
  else if (type == 4) return me::metadata::TagType::MTT_UINT64;
  else if (type == 5) return me::metadata::TagType::MTT_URATIONAL;
  else if (type == 6) return me::metadata::TagType::MTT_INT8;
  else if (type == 7) return me::metadata::TagType::MTT_NAN;
  else if (type == 8) return me::metadata::TagType::MTT_INT16;
  else if (type == 9) return me::metadata::TagType::MTT_INT64;
  else if (type == 10) return me::metadata::TagType::MTT_RATIONAL;
  else if (type == 11) return me::metadata::TagType::MTT_FLOAT32;
  else if (type == 12) return me::metadata::TagType::MTT_FLOAT64;
  return me::metadata::TagType::MTT_NAN;
}

static me::format::tiff_field_type fromMTType(uint16_t type)
{
  if (type == 0) return me::format::tiff_field_type::TIFF_FT_UNDEFINED;
  else if (type == 1) return me::format::tiff_field_type::TIFF_FT_BYTE;
  else if (type == 2) return me::format::tiff_field_type::TIFF_FT_SHORT;
  else if (type == 5) return me::format::tiff_field_type::TIFF_FT_LONG;
  else if (type == 6) return me::format::tiff_field_type::TIFF_FT_RATIONAL;
  else if (type == 7) return me::format::tiff_field_type::TIFF_FT_SBYTE;
  else if (type == 8) return me::format::tiff_field_type::TIFF_FT_SSHORT;
  else if (type == 11) return me::format::tiff_field_type::TIFF_FT_SLONG;
  else if (type == 12) return me::format::tiff_field_type::TIFF_FT_FLOAT;
  else if (type == 13) return me::format::tiff_field_type::TIFF_FT_DOUBLE;
  else if (type == 14) return me::format::tiff_field_type::TIFF_FT_SRATIONAL;
  else if (type == 15) return me::format::tiff_field_type::TIFF_FT_ASCII;
  return me::format::tiff_field_type::TIFF_FT_UNDEFINED;
}

static std::string getTagName(uint16_t tag)
{
  switch(tag)
  {
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_NEW_SUBFILE_TYPE: return "NEW_SUBFILE_TYPE"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_SUBFILE_TYPE: return "SUBFILE_TYPE"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_IMAGE_WIDTH: return "IMAGE_WIDTH"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_IMAGE_LENGTH: return "IMAGE_LENGTH"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_BITS_PER_SAMPLE: return "BITS_PER_SAMPLE"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_COMPRESSION: return "COMPRESSION"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_PHOTOMETRIC_INTERPRETATION: return "PHOTOMETRIC_INTERPRETATION"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_THRESHHOLDING: return "THRESHHOLDING"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_CELL_WIDTH: return "CELL_WIDTH"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_CELL_LENGTH: return "CELL_LENGTH"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_FILL_ORDER: return "FILL_ORDER"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_IMAGE_DESCRIPTION: return "IMAGE_DESCRIPTION"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_MAKE: return "MAKE"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_MODEL: return "MODEL"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_STRIP_OFFSETS: return "STRIP_OFFSETS"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_ORIENTATION: return "ORIENTATION"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_SAMPLES_PER_PIXEL: return "SAMPLES_PER_PIXEL"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_ROWS_PER_STRIP: return "ROWS_PER_STRIP"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_STRIP_BYTE_COUNTS: return "STRIP_BYTE_COUNTS"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_MIN_SAMPLE_VALUE: return "MIN_SAMPLE_VALUE"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_MAX_SAMPLE_VALUE: return "MAX_SAMPLE_VALUE"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_XRESOLUTION: return "XRESOLUTION"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_YRESOLUTION: return "YRESOLUTION"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_PLANAR_CONFIGURATION: return "PLANAR_CONFIGURATION"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_FREE_OFFSETS: return "FREE_OFFSETS"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_FREE_BYTE_COUNTS: return "FREE_BYTE_COUNTS"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_GRAY_RESPONSE_UNIT: return "GRAY_RESPONSE_UNIT"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_GRAY_RESPONSE_CURVE: return "GRAY_RESPONSE_CURVE"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_RESOLUTION_UNIT: return "RESOLUTION_UNIT"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_SOFTWARE: return "SOFTWARE"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_DATE_TIME: return "DATE_TIME"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_ARTIST: return "ARTIST"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_HOST_COMPUTER: return "HOST_COMPUTER"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_COLOR_MAP: return "COLOR_MAP"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_EXTRA_SAMPLES: return "EXTRA_SAMPLES"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_COPYRIGHT: return "COPYRIGHT"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_DOCUMENT_NAME: return "DOCUMENT_NAME"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_PAGE_NAME: return "PAGE_NAME"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_XPOSITION: return "XPOSITION"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_YPOSITION: return "YPOSITION"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_T4OPTIONS: return "T4OPTIONS"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_T6OPTIONS: return "T6OPTIONS"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_PAGE_NUMBER: return "PAGE_NUMBER"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_TRANSFER_FUNCTION: return "TRANSFER_FUNCTION"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_PREDICTOR: return "PREDICTOR"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_WHITE_POINT: return "WHITE_POINT"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_PRIMARY_CHROMATICITIES: return "PRIMARY_CHROMATICITIES"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_HALFTONE_HINTS: return "HALFTONE_HINTS"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_TILE_WIDTH: return "TILE_WIDTH"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_TILE_LENGTH: return "TILE_LENGTH"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_TILE_OFFSETS: return "TILE_OFFSETS"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_TILE_BYTE_COUNTS: return "TILE_BYTE_COUNTS"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_BAD_FAX_LINES: return "BAD_FAX_LINES"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_CLEAN_FAX_DATA: return "CLEAN_FAX_DATA"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_CONSECUTIVE_BAD_FAX_LINES: return "CONSECUTIVE_BAD_FAX_LINES"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_SUB_IFDS: return "SUB_IFDS"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_INK_SET: return "INK_SET"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_INK_NAMES: return "INK_NAMES"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_NUMBER_OF_INKS: return "NUMBER_OF_INKS"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_DOT_RANGE: return "DOT_RANGE"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_TARGET_PRINTER: return "TARGET_PRINTER"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_SAMPLE_FORMAT: return "SAMPLE_FORMAT"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_SMIN_SAMPLE_VALUE: return "SMIN_SAMPLE_VALUE"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_SMAX_SAMPLE_VALUE: return "SMAX_SAMPLE_VALUE"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_TRANSFER_RANGE: return "TRANSFER_RANGE"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_CLIP_PATH: return "CLIP_PATH"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_XCLIP_PATH_UNITS: return "XCLIP_PATH_UNITS"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_YCLIP_PATH_UNITS: return "YCLIP_PATH_UNITS"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_INDEXED: return "INDEXED"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_JPEG_TABLES: return "JPEG_TABLES"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_OPI_PROXY: return "OPI_PROXY"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_GLOBAL_PARAMETERS_IFD: return "GLOBAL_PARAMETERS_IFD"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_PROFILE_TYPE: return "PROFILE_TYPE"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_FAX_PROFILE: return "FAX_PROFILE"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_CODING_METHODS: return "CODING_METHODS"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_VERSION_YEAR: return "VERSION_YEAR"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_MODE_NUMBER: return "MODE_NUMBER"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_DECODE: return "DECODE"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_DEFAULT_IMAGE_COLOR: return "DEFAULT_IMAGE_COLOR"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_JPEG_PROC: return "JPEG_PROC"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_JPEG_INTERCHANGE_FORMAT: return "JPEG_INTERCHANGE_FORMAT"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_JPEG_INTERCHANGE_FORMAT_LENGTH: return "JPEG_INTERCHANGE_FORMAT_LENGTH"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_JPEG_RESTART_INTERVAL: return "JPEG_RESTART_INTERVAL"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_JPEG_LOSSLESS_PREDICTORS: return "JPEG_LOSSLESS_PREDICTORS"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_JPEG_POINT_TRANSFORMS: return "JPEG_POINT_TRANSFORMS"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_JPEGQ_TABLES: return "JPEGQ_TABLES"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_JPEGDC_TABLES: return "JPEGDC_TABLES"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_JPEGAC_TABLES: return "JPEGAC_TABLES"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_YCB_CR_COEFFICIENTS: return "YCB_CR_COEFFICIENTS"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_YCB_CR_SUB_SAMPLING: return "YCB_CR_SUB_SAMPLING"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_YCB_CR_POSITIONING: return "YCB_CR_POSITIONING"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_REFERENCE_BLACK_WHITE: return "REFERENCE_BLACK_WHITE"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_STRIP_ROW_COUNTS: return "STRIP_ROW_COUNTS"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_XMP: return "XMP"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_IMAGE_ID: return "IMAGE_ID"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_IMAGE_LAYER: return "IMAGE_LAYER"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_WANG_ANNOTATION: return "WANG_ANNOTATION"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_MD_FILE_TAG: return "MD_FILE_TAG"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_MD_SCALE_PIXEL: return "MD_SCALE_PIXEL"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_MD_COLOR_TABLE: return "MD_COLOR_TABLE"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_MD_LAB_NAME: return "MD_LAB_NAME"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_MD_SAMPLE_INFO: return "MD_SAMPLE_INFO"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_MD_PREP_DATE: return "MD_PREP_DATE"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_MD_PREP_TIME: return "MD_PREP_TIME"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_MD_FILE_UNITS: return "MD_FILE_UNITS"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_MODEL_PIXEL_SCALE_TAG: return "MODEL_PIXEL_SCALE_TAG"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_IPTC: return "IPTC"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_INGR_PACKET_DATA_TAG: return "INGR_PACKET_DATA_TAG"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_INGR_FLAG_REGISTERS: return "INGR_FLAG_REGISTERS"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_IRASB_TRANSFORMATION_MATRIX: return "IRASB_TRANSFORMATION_MATRIX"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_MODEL_TIEPOINT_TAG: return "MODEL_TIEPOINT_TAG"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_MODEL_TRANSFORMATION_TAG: return "MODEL_TRANSFORMATION_TAG"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_PHOTOSHOP: return "PHOTOSHOP"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_EXIF_IFD: return "EXIF_IFD"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_ICC_PROFILE: return "ICC_PROFILE"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_GEO_KEY_DIRECTORY_TAG: return "GEO_KEY_DIRECTORY_TAG"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_GEO_DOUBLE_PARAMS_TAG: return "GEO_DOUBLE_PARAMS_TAG"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_GEO_ASCII_PARAMS_TAG: return "GEO_ASCII_PARAMS_TAG"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_GPS_IFD: return "GPS_IFD"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_HYLA_FAX_FAC_RECV_PARAMS: return "HYLA_FAX_FAC_RECV_PARAMS"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_HYLA_FAX_FAC_SUB_ADDRESS: return "HYLA_FAX_FAC_SUB_ADDRESS"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_HYLA_FAX_FAC_RECV_TIME: return "HYLA_FAX_FAC_RECV_TIME"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_IMAGE_SOURCE_DATA: return "IMAGE_SOURCE_DATA"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_INTEROPERABILITY_IFD: return "INTEROPERABILITY_IFD"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_GDAL_METADATA: return "GDAL_METADATA"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_GDAL_NODATA: return "GDAL_NODATA"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_OCE_SCANJOB_DESCRIPTION: return "OCE_SCANJOB_DESCRIPTION"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_OCE_APPLICATION_SELECTOR: return "OCE_APPLICATION_SELECTOR"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_OCE_IDENTIFICATION_NUMBER: return "OCE_IDENTIFICATION_NUMBER"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_OCE_IMAGE_LOGIC_CHARACTERISTICS: return "OCE_IMAGE_LOGIC_CHARACTERISTICS"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_DNG_VERSION: return "DNG_VERSION"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_DNG_BACKWARD_VERSION: return "DNG_BACKWARD_VERSION"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_UNIQUE_CAMERA_MODEL: return "UNIQUE_CAMERA_MODEL"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_LOCALIZED_CAMERA_MODEL: return "LOCALIZED_CAMERA_MODEL"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_CFA_PLANE_COLOR: return "CFA_PLANE_COLOR"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_CFA_LAYOUT: return "CFA_LAYOUT"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_LINEARIZATION_TABLE: return "LINEARIZATION_TABLE"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_BLACK_LEVEL_REPEAT_DIM: return "BLACK_LEVEL_REPEAT_DIM"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_BLACK_LEVEL: return "BLACK_LEVEL"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_BLACK_LEVEL_DELTA_H: return "BLACK_LEVEL_DELTA_H"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_BLACK_LEVEL_DELTA_V: return "BLACK_LEVEL_DELTA_V"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_WHITE_LEVEL: return "WHITE_LEVEL"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_DEFAULT_SCALE: return "DEFAULT_SCALE"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_DEFAULT_CROP_ORIGIN: return "DEFAULT_CROP_ORIGIN"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_DEFAULT_CROP_SIZE: return "DEFAULT_CROP_SIZE"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_COLOR_MATRIX1: return "COLOR_MATRIX1"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_COLOR_MATRIX2: return "COLOR_MATRIX2"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_CAMERA_CALIBRATION1: return "CAMERA_CALIBRATION1"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_CAMERA_CALIBRATION2: return "CAMERA_CALIBRATION2"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_REDUCTION_MATRIX1: return "REDUCTION_MATRIX1"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_REDUCTION_MATRIX2: return "REDUCTION_MATRIX2"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_ANALOG_BALANCE: return "ANALOG_BALANCE"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_AS_SHOT_NEUTRAL: return "AS_SHOT_NEUTRAL"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_AS_SHOT_WHITE_XY: return "AS_SHOT_WHITE_XY"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_BASELINE_EXPOSURE: return "BASELINE_EXPOSURE"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_BASELINE_NOISE: return "BASELINE_NOISE"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_BASELINE_SHARPNESS: return "BASELINE_SHARPNESS"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_BAYER_GREEN_SPLIT: return "BAYER_GREEN_SPLIT"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_LINEAR_RESPONSE_LIMIT: return "LINEAR_RESPONSE_LIMIT"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_CAMERA_SERIAL_NUMBER: return "CAMERA_SERIAL_NUMBER"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_LENS_INFO: return "LENS_INFO"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_CHROMA_BLUR_RADIUS: return "CHROMA_BLUR_RADIUS"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_ANTI_ALIAS_STRENGTH: return "ANTI_ALIAS_STRENGTH"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_DNG_PRIVATE_DATA: return "DNG_PRIVATE_DATA"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_MAKER_NOTE_SAFETY: return "MAKER_NOTE_SAFETY"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_CALIBRATION_ILLUMINANT1: return "CALIBRATION_ILLUMINANT1"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_CALIBRATION_ILLUMINANT2: return "CALIBRATION_ILLUMINANT2"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_BEST_QUALITY_SCALE: return "BEST_QUALITY_SCALE"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_ALIAS_LAYER_METADATA: return "ALIAS_LAYER_METADATA"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_TIFF_RSID: return "TIFF_RSID"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_GEO_METADATA: return "GEO_METADATA"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_EXPOSURE_TIME: return "EXPOSURE_TIME"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_F_NUMBER: return "F_NUMBER"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_EXPOSURE_PROGRAM: return "EXPOSURE_PROGRAM"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_SPECTRAL_SENSITIVITY: return "SPECTRAL_SENSITIVITY"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_ISO_SPEED_RATINGS: return "ISO_SPEED_RATINGS"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_OECF: return "OECF"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_EXIF_VERSION: return "EXIF_VERSION"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_DATE_TIME_ORIGINAL: return "DATE_TIME_ORIGINAL"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_DATE_TIME_DIGITIZED: return "DATE_TIME_DIGITIZED"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_COMPONENTS_CONFIGUREATION: return "COMPONENTS_CONFIGUREATION"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_COMPRESSED_BITS_PER_PIXEL: return "COMPRESSED_BITS_PER_PIXEL"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_SHUTTER_SPEED_VALUE: return "SHUTTER_SPEED_VALUE"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_APERTURE_VALUE: return "APERTURE_VALUE"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_BRIGHTNESS_VALUE: return "BRIGHTNESS_VALUE"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_EXPOSURE_BIAS_VALUE: return "EXPOSURE_BIAS_VALUE"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_MAX_APERTURE_VALUE: return "MAX_APERTURE_VALUE"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_SUBJECT_DISTANCE: return "SUBJECT_DISTANCE"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_METERING_MODE: return "METERING_MODE"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_LIGHT_SOURCE: return "LIGHT_SOURCE"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_FLASH: return "FLASH"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_FOCAL_LENGTH: return "FOCAL_LENGTH"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_SUBJECT_AREA: return "SUBJECT_AREA"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_MAKER_NOTE: return "MAKER_NOTE"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_USER_COMMENT: return "USER_COMMENT"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_SUBSEC_TIME: return "SUBSEC_TIME"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_SUBSEC_TIME_ORIGINAL: return "SUBSEC_TIME_ORIGINAL"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_SUBSEC_TIME_DIGITIZED: return "SUBSEC_TIME_DIGITIZED"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_FLASHPIX_VERSION: return "FLASHPIX_VERSION"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_COLOR_SPACE: return "COLOR_SPACE"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_PIXEL_X_DIMENSION: return "PIXEL_X_DIMENSION"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_PIXEL_Y_DIMENSION: return "PIXEL_Y_DIMENSION"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_RELATED_SOUND_FILE: return "RELATED_SOUND_FILE"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_FLASH_ENERGY: return "FLASH_ENERGY"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_SPATIAL_FREQUENCY_RESPONSE: return "SPATIAL_FREQUENCY_RESPONSE"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_FOCAL_PLANE_X_RESOLUTION: return "FOCAL_PLANE_X_RESOLUTION"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_FOCAL_PLANE_Y_RESOLUTION: return "FOCAL_PLANE_Y_RESOLUTION"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_FOCAL_PLANE_RESOLUTION_UNIT: return "FOCAL_PLANE_RESOLUTION_UNIT"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_SUBJECT_LOCATION: return "SUBJECT_LOCATION"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_EXPOSURE_INDEX: return "EXPOSURE_INDEX"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_SENSING_METHOD: return "SENSING_METHOD"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_FILE_SOURCE: return "FILE_SOURCE"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_SCENE_TYPE: return "SCENE_TYPE"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_CFA_PATTERN: return "CFA_PATTERN"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_CUSTOM_RENDERED: return "CUSTOM_RENDERED"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_EXPOSURE_MODE: return "EXPOSURE_MODE"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_WHITE_BALANCE: return "WHITE_BALANCE"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_DIGITAL_ZOOM_RATIO: return "DIGITAL_ZOOM_RATIO"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_FOCAL_LENGTH_IN_35MM_FILM: return "FOCAL_LENGTH_IN_35MM_FILM"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_SCENE_CAPTURE_TYPE: return "SCENE_CAPTURE_TYPE"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_GAIN_CONTROL: return "GAIN_CONTROL"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_CONSTRAST: return "CONSTRAST"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_SATURATION: return "SATURATION"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_SHARPNESS: return "SHARPNESS"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_DEVICE_SETTING_DESCRIPTION: return "DEVICE_SETTING_DESCRIPTION"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_SUBJECT_DISTANCE_RANGE: return "SUBJECT_DISTANCE_RANGE"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_IMAGE_UNIQUE_ID: return "IMAGE_UNIQUE_ID"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_GPS_VERSION_ID: return "GPS_VERSION_ID"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_GPS_LATITUDE_REF: return "GPS_LATITUDE_REF"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_GPS_LATITUDE: return "GPS_LATITUDE"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_GPS_LONGITUDE_REF: return "GPS_LONGITUDE_REF"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_GPS_LONGITUDE: return "GPS_LONGITUDE"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_GPS_ALTITUDE_REF: return "GPS_ALTITUDE_REF"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_GPS_ALTITUDE: return "GPS_ALTITUDE"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_GPS_TIME_STAMP: return "GPS_TIME_STAMP"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_GPS_STATELLITES: return "GPS_STATELLITES"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_GPS_STATUS: return "GPS_STATUS"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_GPS_MEASURE_MODE: return "GPS_MEASURE_MODE"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_GPS_DOP: return "GPS_DOP"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_GPS_SPEED_REF: return "GPS_SPEED_REF"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_GPS_SPEED: return "GPS_SPEED"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_GPS_TRACK_REF: return "GPS_TRACK_REF"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_GPS_TRACK: return "GPS_TRACK"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_GPS_IMG_DIRECTION_REF: return "GPS_IMG_DIRECTION_REF"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_GPS_IMG_DIRECTION: return "GPS_IMG_DIRECTION"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_GPS_MAP_DATUM: return "GPS_MAP_DATUM"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_GPS_DEST_LATITUDE_REF: return "GPS_DEST_LATITUDE_REF"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_GPS_DEST_LATITUDE: return "GPS_DEST_LATITUDE"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_GPS_DEST_LONGITUDE_REF: return "GPS_DEST_LONGITUDE_REF"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_GPS_DEST_LONGITUDE: return "GPS_DEST_LONGITUDE"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_GPS_DEST_BEARING_REF: return "GPS_DEST_BEARING_REF"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_GPS_DEST_BEARING: return "GPS_DEST_BEARING"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_GPS_DEST_DISTANCE_REF: return "GPS_DEST_DISTANCE_REF"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_GPS_DEST_DISTANCE: return "GPS_DEST_DISTANCE"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_GPS_PROCESSING_METHOD: return "GPS_PROCESSING_METHOD"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_GPS_AREA_INFORMATION: return "GPS_AREA_INFORMATION"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_GPS_DATE_STAMP: return "GPS_DATE_STAMP"; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_GPS_DIFFERENTIAL: return "GPS_DIFFERENTIAL"; break;
    default:
      return "UNKNOWN";
    break;
  }
}

static me::format::tiff_ifd_tag getTagFromName(const std::string &tag)
{
  if (tag == "NEW_SUBFILE_TYPE") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_NEW_SUBFILE_TYPE;
  else if (tag == "SUBFILE_TYPE") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_SUBFILE_TYPE;
  else if (tag == "IMAGE_WIDTH") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_IMAGE_WIDTH;
  else if (tag == "IMAGE_LENGTH") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_IMAGE_LENGTH;
  else if (tag == "BITS_PER_SAMPLE") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_BITS_PER_SAMPLE;
  else if (tag == "COMPRESSION") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_COMPRESSION;
  else if (tag == "PHOTOMETRIC_INTERPRETATION") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_PHOTOMETRIC_INTERPRETATION;
  else if (tag == "THRESHHOLDING") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_THRESHHOLDING;
  else if (tag == "CELL_WIDTH") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_CELL_WIDTH;
  else if (tag == "CELL_LENGTH") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_CELL_LENGTH;
  else if (tag == "FILL_ORDER") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_FILL_ORDER;
  else if (tag == "IMAGE_DESCRIPTION") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_IMAGE_DESCRIPTION;
  else if (tag == "MAKE") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_MAKE;
  else if (tag == "MODEL") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_MODEL;
  else if (tag == "STRIP_OFFSETS") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_STRIP_OFFSETS;
  else if (tag == "ORIENTATION") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_ORIENTATION;
  else if (tag == "SAMPLES_PER_PIXEL") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_SAMPLES_PER_PIXEL;
  else if (tag == "ROWS_PER_STRIP") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_ROWS_PER_STRIP;
  else if (tag == "STRIP_BYTE_COUNTS") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_STRIP_BYTE_COUNTS;
  else if (tag == "MIN_SAMPLE_VALUE") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_MIN_SAMPLE_VALUE;
  else if (tag == "MAX_SAMPLE_VALUE") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_MAX_SAMPLE_VALUE;
  else if (tag == "XRESOLUTION") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_XRESOLUTION;
  else if (tag == "YRESOLUTION") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_YRESOLUTION;
  else if (tag == "PLANAR_CONFIGURATION") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_PLANAR_CONFIGURATION;
  else if (tag == "FREE_OFFSETS") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_FREE_OFFSETS;
  else if (tag == "FREE_BYTE_COUNTS") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_FREE_BYTE_COUNTS;
  else if (tag == "GRAY_RESPONSE_UNIT") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_GRAY_RESPONSE_UNIT;
  else if (tag == "GRAY_RESPONSE_CURVE") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_GRAY_RESPONSE_CURVE;
  else if (tag == "RESOLUTION_UNIT") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_RESOLUTION_UNIT;
  else if (tag == "SOFTWARE") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_SOFTWARE;
  else if (tag == "DATE_TIME") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_DATE_TIME;
  else if (tag == "ARTIST") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_ARTIST;
  else if (tag == "HOST_COMPUTER") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_HOST_COMPUTER;
  else if (tag == "COLOR_MAP") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_COLOR_MAP;
  else if (tag == "EXTRA_SAMPLES") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_EXTRA_SAMPLES;
  else if (tag == "COPYRIGHT") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_COPYRIGHT;
  else if (tag == "DOCUMENT_NAME") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_DOCUMENT_NAME;
  else if (tag == "PAGE_NAME") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_PAGE_NAME;
  else if (tag == "XPOSITION") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_XPOSITION;
  else if (tag == "YPOSITION") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_YPOSITION;
  else if (tag == "T4OPTIONS") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_T4OPTIONS;
  else if (tag == "T6OPTIONS") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_T6OPTIONS;
  else if (tag == "PAGE_NUMBER") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_PAGE_NUMBER;
  else if (tag == "TRANSFER_FUNCTION") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_TRANSFER_FUNCTION;
  else if (tag == "PREDICTOR") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_PREDICTOR;
  else if (tag == "WHITE_POINT") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_WHITE_POINT;
  else if (tag == "PRIMARY_CHROMATICITIES") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_PRIMARY_CHROMATICITIES;
  else if (tag == "HALFTONE_HINTS") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_HALFTONE_HINTS;
  else if (tag == "TILE_WIDTH") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_TILE_WIDTH;
  else if (tag == "TILE_LENGTH") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_TILE_LENGTH;
  else if (tag == "TILE_OFFSETS") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_TILE_OFFSETS;
  else if (tag == "TILE_BYTE_COUNTS") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_TILE_BYTE_COUNTS;
  else if (tag == "BAD_FAX_LINES") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_BAD_FAX_LINES;
  else if (tag == "CLEAN_FAX_DATA") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_CLEAN_FAX_DATA;
  else if (tag == "CONSECUTIVE_BAD_FAX_LINES") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_CONSECUTIVE_BAD_FAX_LINES;
  else if (tag == "SUB_IFDS") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_SUB_IFDS;
  else if (tag == "INK_SET") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_INK_SET;
  else if (tag == "INK_NAMES") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_INK_NAMES;
  else if (tag == "NUMBER_OF_INKS") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_NUMBER_OF_INKS;
  else if (tag == "DOT_RANGE") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_DOT_RANGE;
  else if (tag == "TARGET_PRINTER") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_TARGET_PRINTER;
  else if (tag == "SAMPLE_FORMAT") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_SAMPLE_FORMAT;
  else if (tag == "SMIN_SAMPLE_VALUE") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_SMIN_SAMPLE_VALUE;
  else if (tag == "SMAX_SAMPLE_VALUE") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_SMAX_SAMPLE_VALUE;
  else if (tag == "TRANSFER_RANGE") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_TRANSFER_RANGE;
  else if (tag == "CLIP_PATH") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_CLIP_PATH;
  else if (tag == "XCLIP_PATH_UNITS") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_XCLIP_PATH_UNITS;
  else if (tag == "YCLIP_PATH_UNITS") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_YCLIP_PATH_UNITS;
  else if (tag == "INDEXED") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_INDEXED;
  else if (tag == "JPEG_TABLES") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_JPEG_TABLES;
  else if (tag == "OPI_PROXY") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_OPI_PROXY;
  else if (tag == "GLOBAL_PARAMETERS_IFD") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_GLOBAL_PARAMETERS_IFD;
  else if (tag == "PROFILE_TYPE") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_PROFILE_TYPE;
  else if (tag == "FAX_PROFILE") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_FAX_PROFILE;
  else if (tag == "CODING_METHODS") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_CODING_METHODS;
  else if (tag == "VERSION_YEAR") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_VERSION_YEAR;
  else if (tag == "MODE_NUMBER") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_MODE_NUMBER;
  else if (tag == "DECODE") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_DECODE;
  else if (tag == "DEFAULT_IMAGE_COLOR") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_DEFAULT_IMAGE_COLOR;
  else if (tag == "JPEG_PROC") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_JPEG_PROC;
  else if (tag == "JPEG_INTERCHANGE_FORMAT") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_JPEG_INTERCHANGE_FORMAT;
  else if (tag == "JPEG_INTERCHANGE_FORMAT_LENGTH") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_JPEG_INTERCHANGE_FORMAT_LENGTH;
  else if (tag == "JPEG_RESTART_INTERVAL") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_JPEG_RESTART_INTERVAL;
  else if (tag == "JPEG_LOSSLESS_PREDICTORS") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_JPEG_LOSSLESS_PREDICTORS;
  else if (tag == "JPEG_POINT_TRANSFORMS") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_JPEG_POINT_TRANSFORMS;
  else if (tag == "JPEGQ_TABLES") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_JPEGQ_TABLES;
  else if (tag == "JPEGDC_TABLES") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_JPEGDC_TABLES;
  else if (tag == "JPEGAC_TABLES") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_JPEGAC_TABLES;
  else if (tag == "YCB_CR_COEFFICIENTS") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_YCB_CR_COEFFICIENTS;
  else if (tag == "YCB_CR_SUB_SAMPLING") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_YCB_CR_SUB_SAMPLING;
  else if (tag == "YCB_CR_POSITIONING") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_YCB_CR_POSITIONING;
  else if (tag == "REFERENCE_BLACK_WHITE") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_REFERENCE_BLACK_WHITE;
  else if (tag == "STRIP_ROW_COUNTS") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_STRIP_ROW_COUNTS;
  else if (tag == "XMP") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_XMP;
  else if (tag == "IMAGE_ID") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_IMAGE_ID;
  else if (tag == "IMAGE_LAYER") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_IMAGE_LAYER;
  else if (tag == "WANG_ANNOTATION") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_WANG_ANNOTATION;
  else if (tag == "MD_FILE_TAG") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_MD_FILE_TAG;
  else if (tag == "MD_SCALE_PIXEL") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_MD_SCALE_PIXEL;
  else if (tag == "MD_COLOR_TABLE") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_MD_COLOR_TABLE;
  else if (tag == "MD_LAB_NAME") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_MD_LAB_NAME;
  else if (tag == "MD_SAMPLE_INFO") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_MD_SAMPLE_INFO;
  else if (tag == "MD_PREP_DATE") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_MD_PREP_DATE;
  else if (tag == "MD_PREP_TIME") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_MD_PREP_TIME;
  else if (tag == "MD_FILE_UNITS") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_MD_FILE_UNITS;
  else if (tag == "MODEL_PIXEL_SCALE_TAG") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_MODEL_PIXEL_SCALE_TAG;
  else if (tag == "IPTC") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_IPTC;
  else if (tag == "INGR_PACKET_DATA_TAG") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_INGR_PACKET_DATA_TAG;
  else if (tag == "INGR_FLAG_REGISTERS") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_INGR_FLAG_REGISTERS;
  else if (tag == "IRASB_TRANSFORMATION_MATRIX") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_IRASB_TRANSFORMATION_MATRIX;
  else if (tag == "MODEL_TIEPOINT_TAG") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_MODEL_TIEPOINT_TAG;
  else if (tag == "MODEL_TRANSFORMATION_TAG") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_MODEL_TRANSFORMATION_TAG;
  else if (tag == "PHOTOSHOP") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_PHOTOSHOP;
  else if (tag == "EXIF_IFD") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_EXIF_IFD;
  else if (tag == "ICC_PROFILE") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_ICC_PROFILE;
  else if (tag == "GEO_KEY_DIRECTORY_TAG") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_GEO_KEY_DIRECTORY_TAG;
  else if (tag == "GEO_DOUBLE_PARAMS_TAG") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_GEO_DOUBLE_PARAMS_TAG;
  else if (tag == "GEO_ASCII_PARAMS_TAG") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_GEO_ASCII_PARAMS_TAG;
  else if (tag == "GPS_IFD") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_GPS_IFD;
  else if (tag == "HYLA_FAX_FAC_RECV_PARAMS") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_HYLA_FAX_FAC_RECV_PARAMS;
  else if (tag == "HYLA_FAX_FAC_SUB_ADDRESS") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_HYLA_FAX_FAC_SUB_ADDRESS;
  else if (tag == "HYLA_FAX_FAC_RECV_TIME") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_HYLA_FAX_FAC_RECV_TIME;
  else if (tag == "IMAGE_SOURCE_DATA") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_IMAGE_SOURCE_DATA;
  else if (tag == "INTEROPERABILITY_IFD") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_INTEROPERABILITY_IFD;
  else if (tag == "GDAL_METADATA") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_GDAL_METADATA;
  else if (tag == "GDAL_NODATA") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_GDAL_NODATA;
  else if (tag == "OCE_SCANJOB_DESCRIPTION") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_OCE_SCANJOB_DESCRIPTION;
  else if (tag == "OCE_APPLICATION_SELECTOR") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_OCE_APPLICATION_SELECTOR;
  else if (tag == "OCE_IDENTIFICATION_NUMBER") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_OCE_IDENTIFICATION_NUMBER;
  else if (tag == "OCE_IMAGE_LOGIC_CHARACTERISTICS") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_OCE_IMAGE_LOGIC_CHARACTERISTICS;
  else if (tag == "DNG_VERSION") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_DNG_VERSION;
  else if (tag == "DNG_BACKWARD_VERSION") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_DNG_BACKWARD_VERSION;
  else if (tag == "UNIQUE_CAMERA_MODEL") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_UNIQUE_CAMERA_MODEL;
  else if (tag == "LOCALIZED_CAMERA_MODEL") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_LOCALIZED_CAMERA_MODEL;
  else if (tag == "CFA_PLANE_COLOR") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_CFA_PLANE_COLOR;
  else if (tag == "CFA_LAYOUT") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_CFA_LAYOUT;
  else if (tag == "LINEARIZATION_TABLE") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_LINEARIZATION_TABLE;
  else if (tag == "BLACK_LEVEL_REPEAT_DIM") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_BLACK_LEVEL_REPEAT_DIM;
  else if (tag == "BLACK_LEVEL") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_BLACK_LEVEL;
  else if (tag == "BLACK_LEVEL_DELTA_H") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_BLACK_LEVEL_DELTA_H;
  else if (tag == "BLACK_LEVEL_DELTA_V") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_BLACK_LEVEL_DELTA_V;
  else if (tag == "WHITE_LEVEL") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_WHITE_LEVEL;
  else if (tag == "DEFAULT_SCALE") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_DEFAULT_SCALE;
  else if (tag == "DEFAULT_CROP_ORIGIN") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_DEFAULT_CROP_ORIGIN;
  else if (tag == "DEFAULT_CROP_SIZE") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_DEFAULT_CROP_SIZE;
  else if (tag == "COLOR_MATRIX1") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_COLOR_MATRIX1;
  else if (tag == "COLOR_MATRIX2") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_COLOR_MATRIX2;
  else if (tag == "CAMERA_CALIBRATION1") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_CAMERA_CALIBRATION1;
  else if (tag == "CAMERA_CALIBRATION2") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_CAMERA_CALIBRATION2;
  else if (tag == "REDUCTION_MATRIX1") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_REDUCTION_MATRIX1;
  else if (tag == "REDUCTION_MATRIX2") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_REDUCTION_MATRIX2;
  else if (tag == "ANALOG_BALANCE") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_ANALOG_BALANCE;
  else if (tag == "AS_SHOT_NEUTRAL") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_AS_SHOT_NEUTRAL;
  else if (tag == "AS_SHOT_WHITE_XY") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_AS_SHOT_WHITE_XY;
  else if (tag == "BASELINE_EXPOSURE") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_BASELINE_EXPOSURE;
  else if (tag == "BASELINE_NOISE") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_BASELINE_NOISE;
  else if (tag == "BASELINE_SHARPNESS") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_BASELINE_SHARPNESS;
  else if (tag == "BAYER_GREEN_SPLIT") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_BAYER_GREEN_SPLIT;
  else if (tag == "LINEAR_RESPONSE_LIMIT") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_LINEAR_RESPONSE_LIMIT;
  else if (tag == "CAMERA_SERIAL_NUMBER") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_CAMERA_SERIAL_NUMBER;
  else if (tag == "LENS_INFO") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_LENS_INFO;
  else if (tag == "CHROMA_BLUR_RADIUS") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_CHROMA_BLUR_RADIUS;
  else if (tag == "ANTI_ALIAS_STRENGTH") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_ANTI_ALIAS_STRENGTH;
  else if (tag == "DNG_PRIVATE_DATA") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_DNG_PRIVATE_DATA;
  else if (tag == "MAKER_NOTE_SAFETY") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_MAKER_NOTE_SAFETY;
  else if (tag == "CALIBRATION_ILLUMINANT1") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_CALIBRATION_ILLUMINANT1;
  else if (tag == "CALIBRATION_ILLUMINANT2") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_CALIBRATION_ILLUMINANT2;
  else if (tag == "BEST_QUALITY_SCALE") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_BEST_QUALITY_SCALE;
  else if (tag == "ALIAS_LAYER_METADATA") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_ALIAS_LAYER_METADATA;
  else if (tag == "TIFF_RSID") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_TIFF_RSID;
  else if (tag == "GEO_METADATA") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_GEO_METADATA;
  else if (tag == "EXPOSURE_TIME") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_EXPOSURE_TIME;
  else if (tag == "F_NUMBER") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_F_NUMBER;
  else if (tag == "EXPOSURE_PROGRAM") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_EXPOSURE_PROGRAM;
  else if (tag == "SPECTRAL_SENSITIVITY") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_SPECTRAL_SENSITIVITY;
  else if (tag == "ISO_SPEED_RATINGS") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_ISO_SPEED_RATINGS;
  else if (tag == "OECF") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_OECF;
  else if (tag == "EXIF_VERSION") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_EXIF_VERSION;
  else if (tag == "DATE_TIME_ORIGINAL") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_DATE_TIME_ORIGINAL;
  else if (tag == "DATE_TIME_DIGITIZED") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_DATE_TIME_DIGITIZED;
  else if (tag == "COMPONENTS_CONFIGUREATION") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_COMPONENTS_CONFIGUREATION;
  else if (tag == "COMPRESSED_BITS_PER_PIXEL") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_COMPRESSED_BITS_PER_PIXEL;
  else if (tag == "SHUTTER_SPEED_VALUE") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_SHUTTER_SPEED_VALUE;
  else if (tag == "APERTURE_VALUE") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_APERTURE_VALUE;
  else if (tag == "BRIGHTNESS_VALUE") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_BRIGHTNESS_VALUE;
  else if (tag == "EXPOSURE_BIAS_VALUE") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_EXPOSURE_BIAS_VALUE;
  else if (tag == "MAX_APERTURE_VALUE") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_MAX_APERTURE_VALUE;
  else if (tag == "SUBJECT_DISTANCE") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_SUBJECT_DISTANCE;
  else if (tag == "METERING_MODE") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_METERING_MODE;
  else if (tag == "LIGHT_SOURCE") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_LIGHT_SOURCE;
  else if (tag == "FLASH") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_FLASH;
  else if (tag == "FOCAL_LENGTH") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_FOCAL_LENGTH;
  else if (tag == "SUBJECT_AREA") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_SUBJECT_AREA;
  else if (tag == "MAKER_NOTE") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_MAKER_NOTE;
  else if (tag == "USER_COMMENT") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_USER_COMMENT;
  else if (tag == "SUBSEC_TIME") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_SUBSEC_TIME;
  else if (tag == "SUBSEC_TIME_ORIGINAL") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_SUBSEC_TIME_ORIGINAL;
  else if (tag == "SUBSEC_TIME_DIGITIZED") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_SUBSEC_TIME_DIGITIZED;
  else if (tag == "FLASHPIX_VERSION") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_FLASHPIX_VERSION;
  else if (tag == "COLOR_SPACE") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_COLOR_SPACE;
  else if (tag == "PIXEL_X_DIMENSION") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_PIXEL_X_DIMENSION;
  else if (tag == "PIXEL_Y_DIMENSION") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_PIXEL_Y_DIMENSION;
  else if (tag == "RELATED_SOUND_FILE") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_RELATED_SOUND_FILE;
  else if (tag == "FLASH_ENERGY") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_FLASH_ENERGY;
  else if (tag == "SPATIAL_FREQUENCY_RESPONSE") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_SPATIAL_FREQUENCY_RESPONSE;
  else if (tag == "FOCAL_PLANE_X_RESOLUTION") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_FOCAL_PLANE_X_RESOLUTION;
  else if (tag == "FOCAL_PLANE_Y_RESOLUTION") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_FOCAL_PLANE_Y_RESOLUTION;
  else if (tag == "FOCAL_PLANE_RESOLUTION_UNIT") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_FOCAL_PLANE_RESOLUTION_UNIT;
  else if (tag == "SUBJECT_LOCATION") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_SUBJECT_LOCATION;
  else if (tag == "EXPOSURE_INDEX") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_EXPOSURE_INDEX;
  else if (tag == "SENSING_METHOD") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_SENSING_METHOD;
  else if (tag == "FILE_SOURCE") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_FILE_SOURCE;
  else if (tag == "SCENE_TYPE") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_SCENE_TYPE;
  else if (tag == "CFA_PATTERN") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_CFA_PATTERN;
  else if (tag == "CUSTOM_RENDERED") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_CUSTOM_RENDERED;
  else if (tag == "EXPOSURE_MODE") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_EXPOSURE_MODE;
  else if (tag == "WHITE_BALANCE") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_WHITE_BALANCE;
  else if (tag == "DIGITAL_ZOOM_RATIO") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_DIGITAL_ZOOM_RATIO;
  else if (tag == "FOCAL_LENGTH_IN_35MM_FILM") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_FOCAL_LENGTH_IN_35MM_FILM;
  else if (tag == "SCENE_CAPTURE_TYPE") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_SCENE_CAPTURE_TYPE;
  else if (tag == "GAIN_CONTROL") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_GAIN_CONTROL;
  else if (tag == "CONSTRAST") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_CONSTRAST;
  else if (tag == "SATURATION") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_SATURATION;
  else if (tag == "SHARPNESS") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_SHARPNESS;
  else if (tag == "DEVICE_SETTING_DESCRIPTION") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_DEVICE_SETTING_DESCRIPTION;
  else if (tag == "SUBJECT_DISTANCE_RANGE") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_SUBJECT_DISTANCE_RANGE;
  else if (tag == "IMAGE_UNIQUE_ID") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_IMAGE_UNIQUE_ID;
  else if (tag == "GPS_VERSION_ID") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_GPS_VERSION_ID;
  else if (tag == "GPS_LATITUDE_REF") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_GPS_LATITUDE_REF;
  else if (tag == "GPS_LATITUDE") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_GPS_LATITUDE;
  else if (tag == "GPS_LONGITUDE_REF") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_GPS_LONGITUDE_REF;
  else if (tag == "GPS_LONGITUDE") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_GPS_LONGITUDE;
  else if (tag == "GPS_ALTITUDE_REF") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_GPS_ALTITUDE_REF;
  else if (tag == "GPS_ALTITUDE") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_GPS_ALTITUDE;
  else if (tag == "GPS_TIME_STAMP") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_GPS_TIME_STAMP;
  else if (tag == "GPS_STATELLITES") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_GPS_STATELLITES;
  else if (tag == "GPS_STATUS") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_GPS_STATUS;
  else if (tag == "GPS_MEASURE_MODE") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_GPS_MEASURE_MODE;
  else if (tag == "GPS_DOP") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_GPS_DOP;
  else if (tag == "GPS_SPEED_REF") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_GPS_SPEED_REF;
  else if (tag == "GPS_SPEED") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_GPS_SPEED;
  else if (tag == "GPS_TRACK_REF") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_GPS_TRACK_REF;
  else if (tag == "GPS_TRACK") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_GPS_TRACK;
  else if (tag == "GPS_IMG_DIRECTION_REF") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_GPS_IMG_DIRECTION_REF;
  else if (tag == "GPS_IMG_DIRECTION") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_GPS_IMG_DIRECTION;
  else if (tag == "GPS_MAP_DATUM") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_GPS_MAP_DATUM;
  else if (tag == "GPS_DEST_LATITUDE_REF") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_GPS_DEST_LATITUDE_REF;
  else if (tag == "GPS_DEST_LATITUDE") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_GPS_DEST_LATITUDE;
  else if (tag == "GPS_DEST_LONGITUDE_REF") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_GPS_DEST_LONGITUDE_REF;
  else if (tag == "GPS_DEST_LONGITUDE") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_GPS_DEST_LONGITUDE;
  else if (tag == "GPS_DEST_BEARING_REF") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_GPS_DEST_BEARING_REF;
  else if (tag == "GPS_DEST_BEARING") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_GPS_DEST_BEARING;
  else if (tag == "GPS_DEST_DISTANCE_REF") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_GPS_DEST_DISTANCE_REF;
  else if (tag == "GPS_DEST_DISTANCE") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_GPS_DEST_DISTANCE;
  else if (tag == "GPS_PROCESSING_METHOD") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_GPS_PROCESSING_METHOD;
  else if (tag == "GPS_AREA_INFORMATION") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_GPS_AREA_INFORMATION;
  else if (tag == "GPS_DATE_STAMP") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_GPS_DATE_STAMP;
  else if (tag == "GPS_DIFFERENTIAL") return me::format::tiff_ifd_tag::TIFF_IFD_TAG_GPS_DIFFERENTIAL;
  return me::format::tiff_ifd_tag::TIFF_IFD_TAG_UNKNOWN;
}

static uint64_t getFlagFromTag(me::format::tiff_ifd_tag tag)
{
  /* manual sort ;) */
  switch(tag)
  {
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_ARTIST: return FLAG_METADATA_ARTIST; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_PAGE_NAME: return FLAG_METADATA_NAME; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_SOFTWARE: return FLAG_METADATA_SOFTWARE; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_COPYRIGHT: return FLAG_METADATA_COPYRIGHT; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_USER_COMMENT: return FLAG_METADATA_COMMENT; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_IMAGE_DESCRIPTION: return FLAG_METADATA_DESC; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_HOST_COMPUTER: return FLAG_METADATA_HOST_NAME; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_DATE_TIME: return FLAG_METADATA_DATE | FLAG_METADATA_TIME; break;

    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_FILE_SOURCE: return FLAG_METADATA_FILE; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_DOCUMENT_NAME: return FLAG_METADATA_FILE; break;

    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_SUBJECT_AREA: return FLAG_METADATA_SUBJECT; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_SUBJECT_DISTANCE: return FLAG_METADATA_SUBJECT; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_SUBJECT_LOCATION: return FLAG_METADATA_SUBJECT; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_SUBJECT_DISTANCE_RANGE: return FLAG_METADATA_SUBJECT; break;

    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_SCENE_TYPE: return FLAG_METADATA_SCENE; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_LIGHT_SOURCE: return FLAG_METADATA_SCENE; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_METERING_MODE: return FLAG_METADATA_SCENE; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_SCENE_CAPTURE_TYPE: return FLAG_METADATA_SCENE; break;

    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_FLASH: return FLAG_METADATA_CAMERA; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_F_NUMBER: return FLAG_METADATA_CAMERA; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_CONSTRAST: return FLAG_METADATA_CAMERA; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_SHARPNESS: return FLAG_METADATA_CAMERA; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_SATURATION: return FLAG_METADATA_CAMERA; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_COLOR_SPACE: return FLAG_METADATA_CAMERA; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_FLASH_ENERGY: return FLAG_METADATA_CAMERA; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_FOCAL_LENGTH: return FLAG_METADATA_CAMERA; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_EXPOSURE_TIME: return FLAG_METADATA_CAMERA; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_EXPOSURE_MODE: return FLAG_METADATA_CAMERA; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_WHITE_BALANCE: return FLAG_METADATA_CAMERA; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_EXPOSURE_INDEX: return FLAG_METADATA_CAMERA; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_SENSING_METHOD: return FLAG_METADATA_CAMERA; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_APERTURE_VALUE: return FLAG_METADATA_CAMERA; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_EXPOSURE_PROGRAM: return FLAG_METADATA_CAMERA; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_BRIGHTNESS_VALUE: return FLAG_METADATA_CAMERA; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_ISO_SPEED_RATINGS: return FLAG_METADATA_CAMERA; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_MAX_APERTURE_VALUE: return FLAG_METADATA_CAMERA; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_DIGITAL_ZOOM_RATIO: return FLAG_METADATA_CAMERA; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_SHUTTER_SPEED_VALUE: return FLAG_METADATA_CAMERA; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_EXPOSURE_BIAS_VALUE: return FLAG_METADATA_CAMERA; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_FOCAL_LENGTH_IN_35MM_FILM: return FLAG_METADATA_CAMERA; break;
    case me::format::tiff_ifd_tag::TIFF_IFD_TAG_DEVICE_SETTING_DESCRIPTION: return FLAG_METADATA_CAMERA; break;
    default:
      return 0;
    break;
  }
}

static std::string getTIFFMetadataString(me::format::tiff_header &header)
{
  std::string string = "{\n";
  for (auto const &[key, value] : header.IFDs)
  {
    string.append("  ");
    string.append(getTagName(key));
    string.append(": ");
    string.append(value->val(header.byteOrder == 0x4D4D ? me::ByteOrder::BO_LITTLE_ENDIAN : me::ByteOrder::BO_BIG_ENDIAN));
    string.append(",\n");
  }
  string.append("}\n");
  return string;
}

me::format::tiff_ifd* me::format::tiff_format::nextTIFFField(me::bytebuff &buffer)
{
  tiff_ifd* IFD = new tiff_ifd;
  IFD->tag = buffer.pull_uint16();
  IFD->type = getTIFFFieldType(buffer.pull_uint16());
  IFD->nValues = buffer.pull_uint32();
  IFD->offset = buffer.pull_uint32();
  IFD->init(buffer);
  return IFD;
}

void me::format::tiff_format::readTIFFFields(me::bytebuff &buffer, tiff_header &header)
{
  buffer.jump(header.offset);
  header.entries = buffer.pull_uint16();
  std::cout << "[TIFFLoader]: [" << header.entries << "]entries\n";
  for (uint16_t i = 0; i < header.entries; i++)
  {
    tiff_ifd* IFD = nextTIFFField(buffer);
    header.IFDs[IFD->tag] = IFD;
  }
}

void me::format::tiff_format::addTIFFField(me::bytebuff &buffer, uint32_t &offset, tiff_ifd* IFD)
{
  buffer.push_uint16(IFD->tag);
  buffer.push_uint16(IFD->type);
  buffer.push_uint32(IFD->nValues);
  if (IFD->length > 4)
  {
    buffer.push_uint32(offset);
    offset+=IFD->length;
  }else
  {
    /* 4 bytes must be present */
    buffer.push(IFD->value, IFD->length);
    /* adding missing bytes if any */
    uint32_t missing = 4 - IFD->length;
    for (uint8_t j = 0; j < missing; j++)
      buffer.push(0);
  }
}
void me::format::tiff_format::writeTIFFFields(me::bytebuff &buffer, tiff_header &header)
{
  uint32_t offset_start = header.offset + (header.IFDs.size() * 12);
  uint32_t offset = header.offset + (header.IFDs.size() * 12);
  for (auto const &[key, value] : header.IFDs)
    addTIFFField(buffer, offset, value);
  for (auto const &[key, value] : header.IFDs)
    buffer.push(value->value, value->length);
}

void me::format::tiff_format::decompressImage(me::bytebuff* input, me::Image* image)
{
  tiff_decompressor* decompressor = nullptr;
  if (image->info.compression == ME_IMG_COMPRESSION_LZW)
    decompressor = new me::tiff::lzw(input, image);
  decompressor->decode();
}

int me::format::tiff_format::load_image(me::bytebuff &buffer, me::Image* image, uint64_t flags)
{
  tiff_header header;
  header.byteOrder = buffer.pull_uint16();
  if (header.byteOrder == 0x4D4D)
    buffer.byteOrder(me::ByteOrder::BO_LITTLE_ENDIAN);
  else if (header.byteOrder == 0x4949)
    buffer.byteOrder(me::ByteOrder::BO_BIG_ENDIAN);
  else
  {
    std::cout << "[TIFFLoader] [WARN]: bad byte order, assuming little-endian\n";
    buffer.byteOrder(me::ByteOrder::BO_LITTLE_ENDIAN);
  }
  header.magic = buffer.pull_uint16();
  if (header.magic != 0x2A00 && header.magic != 0x002A)
  {
    std::cout << "[TIFFLoader] [ERR]: { filepath: " << buffer.source << " } is not identified as a TIFF\n";
    return ME_ERR;
  }
  header.offset = buffer.pull_uint32();
  readTIFFFields(buffer, header);

  std::cout << "<== TAGS ==>\n";
  std::cout << getTIFFMetadataString(header) << "\n";

  /* -----------------------[ FIELDS ]----------------------- */
    tiff_ifd* PHOTOMETRICINTERPRETATION = header.IFDs[me::format::tiff_ifd_tag::TIFF_IFD_TAG_PHOTOMETRIC_INTERPRETATION];
    tiff_ifd* PLANARCONFIGURATION = header.IFDs[me::format::tiff_ifd_tag::TIFF_IFD_TAG_PLANAR_CONFIGURATION];
    tiff_ifd* COMPRESSION = header.IFDs[me::format::tiff_ifd_tag::TIFF_IFD_TAG_COMPRESSION];
    tiff_ifd* IMAGELENGTH = header.IFDs[me::format::tiff_ifd_tag::TIFF_IFD_TAG_IMAGE_LENGTH];
    tiff_ifd* IMAGEWIDTH = header.IFDs[me::format::tiff_ifd_tag::TIFF_IFD_TAG_IMAGE_WIDTH];
    tiff_ifd* RESOLUTIONUNIT = header.IFDs[me::format::tiff_ifd_tag::TIFF_IFD_TAG_RESOLUTION_UNIT];
    tiff_ifd* XRESOLUTION = header.IFDs[me::format::tiff_ifd_tag::TIFF_IFD_TAG_XRESOLUTION];
    tiff_ifd* YRESOLUTION = header.IFDs[me::format::tiff_ifd_tag::TIFF_IFD_TAG_YRESOLUTION];
    tiff_ifd* THRESHHOLDING = header.IFDs[me::format::tiff_ifd_tag::TIFF_IFD_TAG_THRESHHOLDING];
    tiff_ifd* ROWSPERSTRIP = header.IFDs[me::format::tiff_ifd_tag::TIFF_IFD_TAG_ROWS_PER_STRIP];
    tiff_ifd* STRIPOFFSETS = header.IFDs[me::format::tiff_ifd_tag::TIFF_IFD_TAG_STRIP_OFFSETS];
    tiff_ifd* STRIPBYTECOUNTS = header.IFDs[me::format::tiff_ifd_tag::TIFF_IFD_TAG_STRIP_BYTE_COUNTS];
    tiff_ifd* COLORMAP = header.IFDs[me::format::tiff_ifd_tag::TIFF_IFD_TAG_COLOR_MAP];
    tiff_ifd* SAMPLESPERPIXEL = header.IFDs[me::format::tiff_ifd_tag::TIFF_IFD_TAG_SAMPLES_PER_PIXEL];
    tiff_ifd* BITSPERSAMPLE = header.IFDs[me::format::tiff_ifd_tag::TIFF_IFD_TAG_BITS_PER_SAMPLE];
    tiff_ifd* CELLLENGTH = header.IFDs[me::format::tiff_ifd_tag::TIFF_IFD_TAG_CELL_LENGTH];
    tiff_ifd* CELLWIDTH = header.IFDs[me::format::tiff_ifd_tag::TIFF_IFD_TAG_CELL_WIDTH];
    tiff_ifd* FILLORDER = header.IFDs[me::format::tiff_ifd_tag::TIFF_IFD_TAG_FILL_ORDER];
    tiff_ifd* FREEBYTECOUNTS = header.IFDs[me::format::tiff_ifd_tag::TIFF_IFD_TAG_FREE_BYTE_COUNTS];
    tiff_ifd* FREEOFFSETS = header.IFDs[me::format::tiff_ifd_tag::TIFF_IFD_TAG_FREE_OFFSETS];
    tiff_ifd* GRAYRESPONSECURVE = header.IFDs[me::format::tiff_ifd_tag::TIFF_IFD_TAG_GRAY_RESPONSE_CURVE];
    tiff_ifd* GRAYRESPONSEUNIT = header.IFDs[me::format::tiff_ifd_tag::TIFF_IFD_TAG_GRAY_RESPONSE_UNIT];
    tiff_ifd* MAXSAMPLEVALUE = header.IFDs[me::format::tiff_ifd_tag::TIFF_IFD_TAG_MAX_SAMPLE_VALUE];
    tiff_ifd* MINSAMPLEVALUE = header.IFDs[me::format::tiff_ifd_tag::TIFF_IFD_TAG_MIN_SAMPLE_VALUE];
    tiff_ifd* MODEL = header.IFDs[me::format::tiff_ifd_tag::TIFF_IFD_TAG_MODEL];
    tiff_ifd* NEWSUBFILETYPE = header.IFDs[me::format::tiff_ifd_tag::TIFF_IFD_TAG_NEW_SUBFILE_TYPE];
    tiff_ifd* ORIENTATION = header.IFDs[me::format::tiff_ifd_tag::TIFF_IFD_TAG_ORIENTATION];
    tiff_ifd* ARTIST = header.IFDs[me::format::tiff_ifd_tag::TIFF_IFD_TAG_ARTIST];
    tiff_ifd* COPYRIGHT = header.IFDs[me::format::tiff_ifd_tag::TIFF_IFD_TAG_COPYRIGHT];
    tiff_ifd* DATETIME = header.IFDs[me::format::tiff_ifd_tag::TIFF_IFD_TAG_DATE_TIME];
    tiff_ifd* EXTRASAMPLES = header.IFDs[me::format::tiff_ifd_tag::TIFF_IFD_TAG_EXTRA_SAMPLES];
    tiff_ifd* HOSTCOMPUTER = header.IFDs[me::format::tiff_ifd_tag::TIFF_IFD_TAG_HOST_COMPUTER];
    tiff_ifd* IMAGEDESCRIPTION = header.IFDs[me::format::tiff_ifd_tag::TIFF_IFD_TAG_IMAGE_DESCRIPTION];
    tiff_ifd* SOFTWARE = header.IFDs[me::format::tiff_ifd_tag::TIFF_IFD_TAG_SOFTWARE];
    tiff_ifd* MAKE = header.IFDs[me::format::tiff_ifd_tag::TIFF_IFD_TAG_MAKE];
  /* -------------------------------------------------------- */

  /* check if something is not right */
  if (IMAGEWIDTH == nullptr || IMAGELENGTH == nullptr || BITSPERSAMPLE == nullptr || SAMPLESPERPIXEL == nullptr)
  {
    std::cout << "[TIFFLoader] [ERR]: missing tags\n";
    std::cout << "==> {   ImageWidth,    [0x100] }: " << (IMAGEWIDTH == nullptr ? "\e[33mmissing" : "\e[32mfound") << "\e[0m\n";
    std::cout << "==> {   ImageLength,   [0x101] }: " << (IMAGELENGTH == nullptr ? "\e[33mmissing" : "\e[32mfound") << "\e[0m\n";
    std::cout << "==> {  BitsPerSample,  [0x102] }: " << (BITSPERSAMPLE == nullptr ? "\e[33mmissing" : "\e[32mfound") << "\e[0m\n";
    std::cout << "==> { SamplesPerPixel, [0x115] }: " << (SAMPLESPERPIXEL == nullptr ? "\e[33mmissing" : "\e[32mfound") << "\e[0m\n";
    return ME_ERR;
  }

  /* getting the image width, height and depth */
  uint32_t width = IMAGEWIDTH->asUint(buffer.byte_order), height = IMAGELENGTH->asUint(buffer.byte_order);
  uint8_t depth = (uint8_t) BITSPERSAMPLE->asUint(buffer.byte_order) * SAMPLESPERPIXEL->asUint(buffer.byte_order);
  uint32_t image_size = width * height * (depth / 8);

  /* check if the image width and height is good */
  if (width >= IMAGE_MAX_WIDTH || height >= IMAGE_MAX_HEIGHT)
  {
    if (width >= IMAGE_MAX_WIDTH) std::cout << "[TIFFLoader] [ERR]: image width[" << width << "] out of limit, max width: " << IMAGE_MAX_WIDTH << "\n";
    if (height >= IMAGE_MAX_HEIGHT) std::cout << "[TIFFLoader] [ERR]: image height[" << height << "] out of limit, max height: " << IMAGE_MAX_HEIGHT << "\n";
  }
  std::cout << "[TIFFLoader]: width: " << width << ", height: " << height << ", depth: " << (uint16_t) depth << "\n";

  /* checking the compression type */
  uint16_t compression = COMPRESSION->asUint16(buffer.byte_order);
  if (compression == 1) image->info.compression = ME_IMG_COMPRESSION_NONE;
  else if (compression == 2) image->info.compression = ME_IMG_COMPRESSION_CCITT3;
  else if (compression == 3) image->info.compression = ME_IMG_COMPRESSION_CCITT4;
  else if (compression == 4) image->info.compression = ME_IMG_COMPRESSION_CCITT6;
  else if (compression == 5) image->info.compression = ME_IMG_COMPRESSION_LZW;
  else if (compression == 32773) image->info.compression = ME_IMG_COMPRESSION_PACK_BITS;

  /* creating the "bitmap" */
  image->bitmap = new me::Bitmap;
  image->bitmap->width = width;
  image->bitmap->height = height;
  image->bitmap->bitsPerSample = depth;
  image->bitmap->map = new unsigned char[image_size];

  decompressImage(&buffer, image);
  return ME_FINE;
}

int me::format::tiff_format::write_image(me::bytebuff &buffer, me::Image* image, uint64_t flags)
{
  tiff_header header;
  header.byteOrder = 0x4949;
  header.magic = 0x2A00;
  header.offset = 128;
  buffer.byteOrder(me::ByteOrder::BO_LITTLE_ENDIAN);
  buffer.push_uint16(header.byteOrder);
  buffer.push_uint16(header.magic);
  buffer.push_uint32(header.offset);

  uint16_t compression = 0;
  uint16_t resolution_unit = 10;
  uint64_t x_resolution = (uint64_t) image->bitmap->width / (uint64_t) resolution_unit;
  uint64_t y_resolution = (uint64_t) image->bitmap->height / (uint64_t) resolution_unit;

  /* default tags */
  header.IFDs[TIFF_IFD_TAG_IMAGE_WIDTH] = new tiff_ifd(TIFF_IFD_TAG_IMAGE_WIDTH, tiff_field_type::TIFF_FT_LONG, 1, 0, 8, me::bytebuff::from_uint64(new uint8_t[2], image->bitmap->width, buffer.byte_order));
  header.IFDs[TIFF_IFD_TAG_IMAGE_LENGTH] = new tiff_ifd(TIFF_IFD_TAG_IMAGE_LENGTH, tiff_field_type::TIFF_FT_LONG, 1, 0, 8, me::bytebuff::from_uint64(new uint8_t[2], image->bitmap->height, buffer.byte_order));
  header.IFDs[TIFF_IFD_TAG_BITS_PER_SAMPLE] = new tiff_ifd(TIFF_IFD_TAG_BITS_PER_SAMPLE, tiff_field_type::TIFF_FT_SHORT, 1, 0, 2, me::bytebuff::from_uint16(new uint8_t[2], image->bitmap->bitsPerSample, buffer.byte_order));
  header.IFDs[TIFF_IFD_TAG_COMPRESSION] = new tiff_ifd(TIFF_IFD_TAG_COMPRESSION, tiff_field_type::TIFF_FT_SHORT, 1, 0, 2, me::bytebuff::from_uint16(new uint8_t[2], compression, buffer.byte_order));
  header.IFDs[TIFF_IFD_TAG_PHOTOMETRIC_INTERPRETATION] = new tiff_ifd(TIFF_IFD_TAG_PHOTOMETRIC_INTERPRETATION, tiff_field_type::TIFF_FT_SHORT, 1, 0, 2, me::bytebuff::from_uint16(new uint8_t[2], 1, buffer.byte_order));
  header.IFDs[TIFF_IFD_TAG_STRIP_OFFSETS] = new tiff_ifd(TIFF_IFD_TAG_STRIP_OFFSETS, tiff_field_type::TIFF_FT_SHORT, 1, 0, 2, me::bytebuff::from_uint16(new uint8_t[2], 0, buffer.byte_order)); // TODO: // short or long
  header.IFDs[TIFF_IFD_TAG_SAMPLES_PER_PIXEL] = new tiff_ifd(TIFF_IFD_TAG_SAMPLES_PER_PIXEL, tiff_field_type::TIFF_FT_SHORT, 1, 0, 2, me::bytebuff::from_uint16(new uint8_t[2], image->info.format & 0x00FF, buffer.byte_order));
  header.IFDs[TIFF_IFD_TAG_ROWS_PER_STRIP] = new tiff_ifd(TIFF_IFD_TAG_ROWS_PER_STRIP, tiff_field_type::TIFF_FT_SHORT, 1, 0, 2, me::bytebuff::from_uint16(new uint8_t[2], 0, buffer.byte_order)); // TODO: // short or long
  header.IFDs[TIFF_IFD_TAG_STRIP_BYTE_COUNTS] = new tiff_ifd(TIFF_IFD_TAG_STRIP_BYTE_COUNTS, tiff_field_type::TIFF_FT_SHORT, 1, 0, 2, me::bytebuff::from_uint16(new uint8_t[2], 0, buffer.byte_order)); // TODO: // short or long
  header.IFDs[TIFF_IFD_TAG_XRESOLUTION] = new tiff_ifd(TIFF_IFD_TAG_XRESOLUTION, tiff_field_type::TIFF_FT_RATIONAL, 1, 0, 16, me::bytebuff::from_uint64(new uint8_t[16], x_resolution, buffer.byte_order));
  header.IFDs[TIFF_IFD_TAG_YRESOLUTION] = new tiff_ifd(TIFF_IFD_TAG_YRESOLUTION, tiff_field_type::TIFF_FT_RATIONAL, 1, 0, 16, me::bytebuff::from_uint64(new uint8_t[16], y_resolution, buffer.byte_order));
  header.IFDs[TIFF_IFD_TAG_RESOLUTION_UNIT] = new tiff_ifd(TIFF_IFD_TAG_RESOLUTION_UNIT, tiff_field_type::TIFF_FT_SHORT, 1, 0, 2, me::bytebuff::from_uint16(new uint8_t[2], resolution_unit, buffer.byte_order));
  /* ------------ */

  if (image->info.metadata != nullptr)
  {
    for (auto const &[key, value] : image->info.metadata->tags)
    {
      tiff_ifd_tag tiff_tag = getTagFromName(key);
      uint64_t FLAG = getFlagFromTag(tiff_tag);
      if (tiff_tag != TIFF_IFD_TAG_UNKNOWN && ((flags & FLAG_METADATA_ALL) != 0 || (flags & FLAG) != 0))
      {
        me::format::tiff_field_type type = fromMTType(value->type);
        uint32_t value_size = type & 0x00FF;
        uint32_t value_count = value->length / value_size;
        header.IFDs[tiff_tag] = new tiff_ifd(tiff_tag, type, value_count, 0, value->length, value->value);
        header.entries++;
      }
    }
  }
  writeTIFFFields(buffer, header);
  std::cout << "image written\n";
  return ME_FINE;
}

bool me::format::tiff_format::recognized(me::fileattr &file)
{
  return me::str_ends(file.filepath, ".tif") || me::str_ends(file.filepath, ".tiff");
}

std::vector<std::string> me::format::tiff_format::get_file_exts()
{
  return { "tiff", "tif" };
}

uint64_t me::format::tiff_format::supported_flags()
{
  return (
    FLAG_COMPRESSION_NONE |
    FLAG_COMPRESSION_DEFLATE |
    FLAG_COMPRESSION_LZW |
    FLAG_COMPRESSION_PACK_BITS |

    FLAG_METADATA_ALL |
    FLAG_IMAGE_BW |
    FLAG_IMAGE_RGB |
    FLAG_IMAGE_RGBA |
    FLAG_IMAGE_DEPTH8 |
    FLAG_IMAGE_DEPTH16
  );
}