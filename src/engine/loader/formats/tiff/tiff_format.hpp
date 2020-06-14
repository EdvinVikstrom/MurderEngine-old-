#ifndef TIFF_FORMAT_H
  #define TIFF_FORMAT_H

#include "../../image_format.hpp"

namespace me {
  
  namespace format {
    
    enum tiff_ifd_tag : uint16_t {
      TIFF_IFD_TAG_UNKNOWN =                           0xFAFA,
      TIFF_IFD_TAG_NEW_SUBFILE_TYPE =                  0x00FE,
      TIFF_IFD_TAG_SUBFILE_TYPE =                      0x00FF,
      TIFF_IFD_TAG_IMAGE_WIDTH =                       0x0100,
      TIFF_IFD_TAG_IMAGE_LENGTH =                      0x0101,
      TIFF_IFD_TAG_BITS_PER_SAMPLE =                   0x0102,
      TIFF_IFD_TAG_COMPRESSION =                       0x0103,
      TIFF_IFD_TAG_PHOTOMETRIC_INTERPRETATION =        0x0106,
      TIFF_IFD_TAG_THRESHHOLDING =                     0x0107,
      TIFF_IFD_TAG_CELL_WIDTH =                        0x0108,
      TIFF_IFD_TAG_CELL_LENGTH =                       0x0109,
      TIFF_IFD_TAG_FILL_ORDER =                        0x010A,
      TIFF_IFD_TAG_IMAGE_DESCRIPTION =                 0x010E,
      TIFF_IFD_TAG_MAKE =                              0x010F,
      TIFF_IFD_TAG_MODEL =                             0x0110,
      TIFF_IFD_TAG_STRIP_OFFSETS =                     0x0111,
      TIFF_IFD_TAG_ORIENTATION =                       0x0112,
      TIFF_IFD_TAG_SAMPLES_PER_PIXEL =                 0x0115,
      TIFF_IFD_TAG_ROWS_PER_STRIP =                    0x0116,
      TIFF_IFD_TAG_STRIP_BYTE_COUNTS =                 0x0117,
      TIFF_IFD_TAG_MIN_SAMPLE_VALUE =                  0x0118,
      TIFF_IFD_TAG_MAX_SAMPLE_VALUE =                  0x0119,
      TIFF_IFD_TAG_XRESOLUTION =                       0x011A,
      TIFF_IFD_TAG_YRESOLUTION =                       0x011B,
      TIFF_IFD_TAG_PLANAR_CONFIGURATION =              0x011C,
      TIFF_IFD_TAG_FREE_OFFSETS =                      0x0120,
      TIFF_IFD_TAG_FREE_BYTE_COUNTS =                  0x0121,
      TIFF_IFD_TAG_GRAY_RESPONSE_UNIT =                0x0122,
      TIFF_IFD_TAG_GRAY_RESPONSE_CURVE =               0x0123,
      TIFF_IFD_TAG_RESOLUTION_UNIT =                   0x0128,
      TIFF_IFD_TAG_SOFTWARE =                          0x0131,
      TIFF_IFD_TAG_DATE_TIME =                         0x0132,
      TIFF_IFD_TAG_ARTIST =                            0x013B,
      TIFF_IFD_TAG_HOST_COMPUTER =                     0x013C,
      TIFF_IFD_TAG_COLOR_MAP =                         0x0140,
      TIFF_IFD_TAG_EXTRA_SAMPLES =                     0x0152,
      TIFF_IFD_TAG_COPYRIGHT =                         0x8298,
      
      TIFF_IFD_TAG_DOCUMENT_NAME =                     0x010D,
      TIFF_IFD_TAG_PAGE_NAME =                         0x011D,
      TIFF_IFD_TAG_XPOSITION =                         0x011E,
      TIFF_IFD_TAG_YPOSITION =                         0x011F,
      TIFF_IFD_TAG_T4OPTIONS =                         0x0124,
      TIFF_IFD_TAG_T6OPTIONS =                         0x0125,
      TIFF_IFD_TAG_PAGE_NUMBER =                       0x0129,
      TIFF_IFD_TAG_TRANSFER_FUNCTION =                 0x012D,
      TIFF_IFD_TAG_PREDICTOR =                         0x013D,
      TIFF_IFD_TAG_WHITE_POINT =                       0x013E,
      TIFF_IFD_TAG_PRIMARY_CHROMATICITIES =            0x013F,
      TIFF_IFD_TAG_HALFTONE_HINTS =                    0x0141,
      TIFF_IFD_TAG_TILE_WIDTH =                        0x0142,
      TIFF_IFD_TAG_TILE_LENGTH =                       0x0143,
      TIFF_IFD_TAG_TILE_OFFSETS =                      0x0144,
      TIFF_IFD_TAG_TILE_BYTE_COUNTS =                  0x0145,
      TIFF_IFD_TAG_BAD_FAX_LINES =                     0x0146,
      TIFF_IFD_TAG_CLEAN_FAX_DATA =                    0x0147,
      TIFF_IFD_TAG_CONSECUTIVE_BAD_FAX_LINES =         0x0148,
      TIFF_IFD_TAG_SUB_IFDS =                          0x014A,
      TIFF_IFD_TAG_INK_SET =                           0x014C,
      TIFF_IFD_TAG_INK_NAMES =                         0x014D,
      TIFF_IFD_TAG_NUMBER_OF_INKS =                    0x014E,
      TIFF_IFD_TAG_DOT_RANGE =                         0x0150,
      TIFF_IFD_TAG_TARGET_PRINTER =                    0x0151,
      TIFF_IFD_TAG_SAMPLE_FORMAT =                     0x0153,
      TIFF_IFD_TAG_SMIN_SAMPLE_VALUE =                 0x0154,
      TIFF_IFD_TAG_SMAX_SAMPLE_VALUE =                 0x0155,
      TIFF_IFD_TAG_TRANSFER_RANGE =                    0x0156,
      TIFF_IFD_TAG_CLIP_PATH =                         0x0157,
      TIFF_IFD_TAG_XCLIP_PATH_UNITS =                  0x0158,
      TIFF_IFD_TAG_YCLIP_PATH_UNITS =                  0x0159,
      TIFF_IFD_TAG_INDEXED =                           0x015A,
      TIFF_IFD_TAG_JPEG_TABLES =                       0x015B,
      TIFF_IFD_TAG_OPI_PROXY =                         0x015F,
      TIFF_IFD_TAG_GLOBAL_PARAMETERS_IFD =             0x0190,
      TIFF_IFD_TAG_PROFILE_TYPE =                      0x0191,
      TIFF_IFD_TAG_FAX_PROFILE =                       0x0192,
      TIFF_IFD_TAG_CODING_METHODS =                    0x0193,
      TIFF_IFD_TAG_VERSION_YEAR =                      0x0194,
      TIFF_IFD_TAG_MODE_NUMBER =                       0x0195,
      TIFF_IFD_TAG_DECODE =                            0x01B1,
      TIFF_IFD_TAG_DEFAULT_IMAGE_COLOR =               0x01B2,
      TIFF_IFD_TAG_JPEG_PROC =                         0x0200,
      TIFF_IFD_TAG_JPEG_INTERCHANGE_FORMAT =           0x0201,
      TIFF_IFD_TAG_JPEG_INTERCHANGE_FORMAT_LENGTH =    0x0202,
      TIFF_IFD_TAG_JPEG_RESTART_INTERVAL =             0x0203,
      TIFF_IFD_TAG_JPEG_LOSSLESS_PREDICTORS =          0x0205,
      TIFF_IFD_TAG_JPEG_POINT_TRANSFORMS =             0x0206,
      TIFF_IFD_TAG_JPEGQ_TABLES =                      0x0207,
      TIFF_IFD_TAG_JPEGDC_TABLES =                     0x0208,
      TIFF_IFD_TAG_JPEGAC_TABLES =                     0x0209,
      TIFF_IFD_TAG_YCB_CR_COEFFICIENTS =               0x0211,
      TIFF_IFD_TAG_YCB_CR_SUB_SAMPLING =               0x0212,
      TIFF_IFD_TAG_YCB_CR_POSITIONING =                0x0213,
      TIFF_IFD_TAG_REFERENCE_BLACK_WHITE =             0x0214,
      TIFF_IFD_TAG_STRIP_ROW_COUNTS =                  0x022F,
      TIFF_IFD_TAG_XMP =                               0x02BC,
      TIFF_IFD_TAG_IMAGE_ID =                          0x800D,
      TIFF_IFD_TAG_IMAGE_LAYER =                       0x87AC,
      
      TIFF_IFD_TAG_WANG_ANNOTATION =                   0x80A4,
      TIFF_IFD_TAG_MD_FILE_TAG =                       0x82A5,
      TIFF_IFD_TAG_MD_SCALE_PIXEL =                    0x82A6,
      TIFF_IFD_TAG_MD_COLOR_TABLE =                    0x82A7,
      TIFF_IFD_TAG_MD_LAB_NAME =                       0x82A8,
      TIFF_IFD_TAG_MD_SAMPLE_INFO =                    0x82A9,
      TIFF_IFD_TAG_MD_PREP_DATE =                      0x82AA,
      TIFF_IFD_TAG_MD_PREP_TIME =                      0x82AB,
      TIFF_IFD_TAG_MD_FILE_UNITS =                     0x82AC,
      TIFF_IFD_TAG_MODEL_PIXEL_SCALE_TAG =             0x830E,
      TIFF_IFD_TAG_IPTC =                              0x83BB,
      TIFF_IFD_TAG_INGR_PACKET_DATA_TAG =              0x847E,
      TIFF_IFD_TAG_INGR_FLAG_REGISTERS =               0x847F,
      TIFF_IFD_TAG_IRASB_TRANSFORMATION_MATRIX =       0x8480,
      TIFF_IFD_TAG_MODEL_TIEPOINT_TAG =                0x8482,
      TIFF_IFD_TAG_MODEL_TRANSFORMATION_TAG =          0x85D8,
      TIFF_IFD_TAG_PHOTOSHOP =                         0x8649,
      TIFF_IFD_TAG_EXIF_IFD =                          0x8769,
      TIFF_IFD_TAG_ICC_PROFILE =                       0x8773,
      TIFF_IFD_TAG_GEO_KEY_DIRECTORY_TAG =             0x87AF,
      TIFF_IFD_TAG_GEO_DOUBLE_PARAMS_TAG =             0x87B0,
      TIFF_IFD_TAG_GEO_ASCII_PARAMS_TAG =              0x87B1,
      TIFF_IFD_TAG_GPS_IFD =                           0x8825,
      TIFF_IFD_TAG_HYLA_FAX_FAC_RECV_PARAMS =          0x885C,
      TIFF_IFD_TAG_HYLA_FAX_FAC_SUB_ADDRESS =          0x885D,
      TIFF_IFD_TAG_HYLA_FAX_FAC_RECV_TIME =            0x885E,
      TIFF_IFD_TAG_IMAGE_SOURCE_DATA =                 0x935C,
      TIFF_IFD_TAG_INTEROPERABILITY_IFD =              0xA005,
      TIFF_IFD_TAG_GDAL_METADATA =                     0xA480,
      TIFF_IFD_TAG_GDAL_NODATA =                       0xA481,
      TIFF_IFD_TAG_OCE_SCANJOB_DESCRIPTION =           0xC427,
      TIFF_IFD_TAG_OCE_APPLICATION_SELECTOR =          0xC428,
      TIFF_IFD_TAG_OCE_IDENTIFICATION_NUMBER =         0xC429,
      TIFF_IFD_TAG_OCE_IMAGE_LOGIC_CHARACTERISTICS =   0xC42A,
      TIFF_IFD_TAG_DNG_VERSION =                       0xC612,
      TIFF_IFD_TAG_DNG_BACKWARD_VERSION =              0xC613,
      TIFF_IFD_TAG_UNIQUE_CAMERA_MODEL =               0xC614,
      TIFF_IFD_TAG_LOCALIZED_CAMERA_MODEL =            0xC615,
      TIFF_IFD_TAG_CFA_PLANE_COLOR =                   0xC616,
      TIFF_IFD_TAG_CFA_LAYOUT =                        0xC617,
      TIFF_IFD_TAG_LINEARIZATION_TABLE =               0xC618,
      TIFF_IFD_TAG_BLACK_LEVEL_REPEAT_DIM =            0xC619,
      TIFF_IFD_TAG_BLACK_LEVEL =                       0xC61A,
      TIFF_IFD_TAG_BLACK_LEVEL_DELTA_H =               0xC61B,
      TIFF_IFD_TAG_BLACK_LEVEL_DELTA_V =               0xC61C,
      TIFF_IFD_TAG_WHITE_LEVEL =                       0xC61D,
      TIFF_IFD_TAG_DEFAULT_SCALE =                     0xC61E,
      TIFF_IFD_TAG_DEFAULT_CROP_ORIGIN =               0xC61F,
      TIFF_IFD_TAG_DEFAULT_CROP_SIZE =                 0xC620,
      TIFF_IFD_TAG_COLOR_MATRIX1 =                     0xC621,
      TIFF_IFD_TAG_COLOR_MATRIX2 =                     0xC622,
      TIFF_IFD_TAG_CAMERA_CALIBRATION1 =               0xC623,
      TIFF_IFD_TAG_CAMERA_CALIBRATION2 =               0xC624,
      TIFF_IFD_TAG_REDUCTION_MATRIX1 =                 0xC625,
      TIFF_IFD_TAG_REDUCTION_MATRIX2 =                 0xC626,
      TIFF_IFD_TAG_ANALOG_BALANCE =                    0xC627,
      TIFF_IFD_TAG_AS_SHOT_NEUTRAL =                   0xC628,
      TIFF_IFD_TAG_AS_SHOT_WHITE_XY =                  0xC629,
      TIFF_IFD_TAG_BASELINE_EXPOSURE =                 0xC62A,
      TIFF_IFD_TAG_BASELINE_NOISE =                    0xC62B,
      TIFF_IFD_TAG_BASELINE_SHARPNESS =                0xC62C,
      TIFF_IFD_TAG_BAYER_GREEN_SPLIT =                 0xC62D,
      TIFF_IFD_TAG_LINEAR_RESPONSE_LIMIT =             0xC62E,
      TIFF_IFD_TAG_CAMERA_SERIAL_NUMBER =              0xC62F,
      TIFF_IFD_TAG_LENS_INFO =                         0xC630,
      TIFF_IFD_TAG_CHROMA_BLUR_RADIUS =                0xC631,
      TIFF_IFD_TAG_ANTI_ALIAS_STRENGTH =               0xC632,
      TIFF_IFD_TAG_DNG_PRIVATE_DATA =                  0xC634,
      TIFF_IFD_TAG_MAKER_NOTE_SAFETY =                 0xC635,
      TIFF_IFD_TAG_CALIBRATION_ILLUMINANT1 =           0xC65A,
      TIFF_IFD_TAG_CALIBRATION_ILLUMINANT2 =           0xC65B,
      TIFF_IFD_TAG_BEST_QUALITY_SCALE =                0xC65C,
      TIFF_IFD_TAG_ALIAS_LAYER_METADATA =              0xC660,
      TIFF_IFD_TAG_TIFF_RSID =                         0xC6DC,
      TIFF_IFD_TAG_GEO_METADATA =                      0xC6DD,
      
      TIFF_IFD_TAG_EXPOSURE_TIME =                     0x829A,
      TIFF_IFD_TAG_F_NUMBER =                          0x829D,
      TIFF_IFD_TAG_EXPOSURE_PROGRAM =                  0x8822,
      TIFF_IFD_TAG_SPECTRAL_SENSITIVITY =              0x8824,
      TIFF_IFD_TAG_ISO_SPEED_RATINGS =                 0x8827,
      TIFF_IFD_TAG_OECF =                              0x8828,
      TIFF_IFD_TAG_EXIF_VERSION =                      0x9000,
      TIFF_IFD_TAG_DATE_TIME_ORIGINAL =                0x9003,
      TIFF_IFD_TAG_DATE_TIME_DIGITIZED =               0x9004,
      TIFF_IFD_TAG_COMPONENTS_CONFIGUREATION =         0x9101,
      TIFF_IFD_TAG_COMPRESSED_BITS_PER_PIXEL =         0x9102,
      TIFF_IFD_TAG_SHUTTER_SPEED_VALUE =               0x9201,
      TIFF_IFD_TAG_APERTURE_VALUE =                    0x9202,
      TIFF_IFD_TAG_BRIGHTNESS_VALUE =                  0x9203,
      TIFF_IFD_TAG_EXPOSURE_BIAS_VALUE =               0x9204,
      TIFF_IFD_TAG_MAX_APERTURE_VALUE =                0x9205,
      TIFF_IFD_TAG_SUBJECT_DISTANCE =                  0x9206,
      TIFF_IFD_TAG_METERING_MODE =                     0x9207,
      TIFF_IFD_TAG_LIGHT_SOURCE =                      0x9208,
      TIFF_IFD_TAG_FLASH =                             0x9209,
      TIFF_IFD_TAG_FOCAL_LENGTH =                      0x920A,
      TIFF_IFD_TAG_SUBJECT_AREA =                      0x9214,
      TIFF_IFD_TAG_MAKER_NOTE =                        0x927C,
      TIFF_IFD_TAG_USER_COMMENT =                      0x9286,
      TIFF_IFD_TAG_SUBSEC_TIME =                       0x9290,
      TIFF_IFD_TAG_SUBSEC_TIME_ORIGINAL =              0x9291,
      TIFF_IFD_TAG_SUBSEC_TIME_DIGITIZED =             0x9292,
      TIFF_IFD_TAG_FLASHPIX_VERSION =                  0xA000,
      TIFF_IFD_TAG_COLOR_SPACE =                       0xA001,
      TIFF_IFD_TAG_PIXEL_X_DIMENSION =                 0xA002,
      TIFF_IFD_TAG_PIXEL_Y_DIMENSION =                 0xA003,
      TIFF_IFD_TAG_RELATED_SOUND_FILE =                0xA004,
      TIFF_IFD_TAG_FLASH_ENERGY =                      0xA20B,
      TIFF_IFD_TAG_SPATIAL_FREQUENCY_RESPONSE =        0xA20C,
      TIFF_IFD_TAG_FOCAL_PLANE_X_RESOLUTION =          0xA20E,
      TIFF_IFD_TAG_FOCAL_PLANE_Y_RESOLUTION =          0xA20F,
      TIFF_IFD_TAG_FOCAL_PLANE_RESOLUTION_UNIT =       0xA210,
      TIFF_IFD_TAG_SUBJECT_LOCATION =                  0xA214,
      TIFF_IFD_TAG_EXPOSURE_INDEX =                    0xA215,
      TIFF_IFD_TAG_SENSING_METHOD =                    0xA217,
      TIFF_IFD_TAG_FILE_SOURCE =                       0xA300,
      TIFF_IFD_TAG_SCENE_TYPE =                        0xA301,
      TIFF_IFD_TAG_CFA_PATTERN =                       0xA302,
      TIFF_IFD_TAG_CUSTOM_RENDERED =                   0xA401,
      TIFF_IFD_TAG_EXPOSURE_MODE =                     0xA402,
      TIFF_IFD_TAG_WHITE_BALANCE =                     0xA403,
      TIFF_IFD_TAG_DIGITAL_ZOOM_RATIO =                0xA404,
      TIFF_IFD_TAG_FOCAL_LENGTH_IN_35MM_FILM =         0xA405,
      TIFF_IFD_TAG_SCENE_CAPTURE_TYPE =                0xA406,
      TIFF_IFD_TAG_GAIN_CONTROL =                      0xA407,
      TIFF_IFD_TAG_CONSTRAST =                         0xA408,
      TIFF_IFD_TAG_SATURATION =                        0xA409,
      TIFF_IFD_TAG_SHARPNESS =                         0xA40A,
      TIFF_IFD_TAG_DEVICE_SETTING_DESCRIPTION =        0xA40B,
      TIFF_IFD_TAG_SUBJECT_DISTANCE_RANGE =            0xA40C,
      TIFF_IFD_TAG_IMAGE_UNIQUE_ID =                   0xA420,
      
      TIFF_IFD_TAG_GPS_VERSION_ID =                    0x0000,
      TIFF_IFD_TAG_GPS_LATITUDE_REF =                  0x0001,
      TIFF_IFD_TAG_GPS_LATITUDE =                      0x0002,
      TIFF_IFD_TAG_GPS_LONGITUDE_REF =                 0x0003,
      TIFF_IFD_TAG_GPS_LONGITUDE =                     0x0004,
      TIFF_IFD_TAG_GPS_ALTITUDE_REF =                  0x0005,
      TIFF_IFD_TAG_GPS_ALTITUDE =                      0x0006,
      TIFF_IFD_TAG_GPS_TIME_STAMP =                    0x0007,
      TIFF_IFD_TAG_GPS_STATELLITES =                   0x0008,
      TIFF_IFD_TAG_GPS_STATUS =                        0x0009,
      TIFF_IFD_TAG_GPS_MEASURE_MODE =                  0x000A,
      TIFF_IFD_TAG_GPS_DOP =                           0x000B,
      TIFF_IFD_TAG_GPS_SPEED_REF =                     0x000C,
      TIFF_IFD_TAG_GPS_SPEED =                         0x000D,
      TIFF_IFD_TAG_GPS_TRACK_REF =                     0x000E,
      TIFF_IFD_TAG_GPS_TRACK =                         0x000F,
      TIFF_IFD_TAG_GPS_IMG_DIRECTION_REF =             0x0010,
      TIFF_IFD_TAG_GPS_IMG_DIRECTION =                 0x0011,
      TIFF_IFD_TAG_GPS_MAP_DATUM =                     0x0012,
      TIFF_IFD_TAG_GPS_DEST_LATITUDE_REF =             0x0013,
      TIFF_IFD_TAG_GPS_DEST_LATITUDE =                 0x0014,
      TIFF_IFD_TAG_GPS_DEST_LONGITUDE_REF =            0x0015,
      TIFF_IFD_TAG_GPS_DEST_LONGITUDE =                0x0016,
      TIFF_IFD_TAG_GPS_DEST_BEARING_REF =              0x0017,
      TIFF_IFD_TAG_GPS_DEST_BEARING =                  0x0018,
      TIFF_IFD_TAG_GPS_DEST_DISTANCE_REF =             0x0019,
      TIFF_IFD_TAG_GPS_DEST_DISTANCE =                 0x001A,
      TIFF_IFD_TAG_GPS_PROCESSING_METHOD =             0x001B,
      TIFF_IFD_TAG_GPS_AREA_INFORMATION =              0x001C,
      TIFF_IFD_TAG_GPS_DATE_STAMP =                    0x001D,
      TIFF_IFD_TAG_GPS_DIFFERENTIAL =                  0x001E
    };
    
    enum tiff_field_type : uint16_t {
      TIFF_FT_BYTE = 0x0101,
      TIFF_FT_ASCII = 0x0201,
      TIFF_FT_SHORT = 0x0302,
      TIFF_FT_LONG = 0x0408,
      TIFF_FT_RATIONAL = 0x0510,
      TIFF_FT_SBYTE = 0x0601,
      TIFF_FT_UNDEFINED = 0x0701,
      TIFF_FT_SSHORT = 0x0802,
      TIFF_FT_SLONG = 0x0908,
      TIFF_FT_SRATIONAL = 0x0A10,
      TIFF_FT_FLOAT = 0x0B04,
      TIFF_FT_DOUBLE = 0x0C08
    };
    
    struct tiff_ifd {
      uint16_t tag;
      tiff_field_type type;
      uint32_t nValues;
      uint32_t offset;
      
      uint32_t length = 0;
      uint8_t* value = nullptr;
      
      tiff_ifd(uint16_t tag, tiff_field_type type, uint32_t nValues, uint32_t offset, uint32_t length, uint8_t* value)
      {
        this->tag = tag;
        this->type = type;
        this->nValues = nValues;
        this->offset = offset;
        this->length = length;
        this->value = value;
      }
      
      tiff_ifd() { }
      
      void init(me::bytebuff &buffer)
      {
        uint32_t size = type & 0x00FF;
        length = nValues * size;
        if (length <= 4)
        {
          value = me::bytebuff::from_uint32(new uint8_t[4], offset, buffer.byte_order);
        }else
        {
          uint64_t old_pos = buffer.pos;
          buffer.jump(offset);
          value = buffer.pull(new uint8_t[length], length);
          buffer.jump(old_pos);
        }
      }
      
      uint16_t asUint16(me::ByteOrder order)
      {
        return me::bytebuff::to_uint16(value, order);
      }
      uint32_t asUint32(me::ByteOrder order)
      {
        return me::bytebuff::to_uint32(value, order);
      }
      uint32_t asUint64(me::ByteOrder order)
      {
        return me::bytebuff::to_uint64(value, order);
      }
      
      uint64_t* asRational(me::ByteOrder order)
      {
        return new uint64_t[2] {
          me::bytebuff::to_uint64(value, order),
          me::bytebuff::to_uint64(value, 8, order)
        };
      }
      
      uint64_t asUint(me::ByteOrder order)
      {
        if (type == TIFF_FT_BYTE)
        return value[0];
        else if (type == TIFF_FT_SHORT)
        return me::bytebuff::to_uint16(value, order);
        else if (type == TIFF_FT_LONG)
        return me::bytebuff::to_uint64(value, order);
        return 0;
      }
      
      std::string asASCII()
      {
        return std::string((const char*) value, length);
      }
      
      std::string val(me::ByteOrder order)
      {
        if (type == TIFF_FT_BYTE) return std::to_string(value[0]);
        else if (type == TIFF_FT_ASCII) return asASCII();
        else if (type == TIFF_FT_SHORT) return std::to_string(asUint16(order));
        else if (type == TIFF_FT_LONG) return std::to_string(asUint64(order));
        else if (type == TIFF_FT_RATIONAL)
        {
          uint64_t* rational = asRational(order);
          return std::to_string(rational[0]) + ", " + std::to_string(rational[1]);
        }
        else if (type == TIFF_FT_SBYTE) return std::to_string((char) value[0]);
        else if (type == TIFF_FT_UNDEFINED) return "undefined";
        else if (type == TIFF_FT_SSHORT) return std::to_string((short) asUint16(order));
        else if (type == TIFF_FT_SLONG) return std::to_string((long) asUint64(order));
        else if (type == TIFF_FT_SRATIONAL)
        {
          uint64_t* rational = asRational(order);
          return std::to_string((long) rational[0]) + ", " + std::to_string((long) rational[1]);
        }
        else if (type == TIFF_FT_FLOAT) return "FLOAT";
        else if (type == TIFF_FT_DOUBLE) return "DOUBLE";
        return "NO TYPE";
      }
      
    };
    
    struct tiff_header {
      uint16_t byteOrder = 0x4D4D;
      uint16_t magic = 0x4A00;
      uint32_t offset = 0;
      uint16_t entries = 0;
      std::map<uint16_t, tiff_ifd*> IFDs;
    };
    
    struct tiff_decompressor {
      
      me::bytebuff* inputStream = nullptr;
      me::Image* image = nullptr;
      
      tiff_decompressor(me::bytebuff* inputStream, me::Image* image)
      {
        this->inputStream = inputStream;
        this->image = image;
      }
      
      virtual int decode() = 0;
      
    };
    
    struct tiff_format : image_format {
      
      tiff_format() : image_format(IFF_TIFF) { }
      
      tiff_ifd* nextTIFFField(me::bytebuff &buffer);
      void readTIFFFields(me::bytebuff &buffer, tiff_header &header);
      
      void addTIFFField(me::bytebuff &buffer, uint32_t &offset, tiff_ifd* IFD);
      void writeTIFFFields(me::bytebuff &buffer, tiff_header &header);
      
      void decompressImage(me::bytebuff* input, me::Image* image);
      void compressImage(me::Image* image, me::bytebuff* output);
      
      int load_image(me::bytebuff &buffer, me::Image* image, uint64_t flags) override;
      int write_image(me::bytebuff &buffer, me::Image* image, uint64_t flags) override;
      bool recognized(me::fileattr &file) override;
      std::vector<std::string> get_file_exts() override;
      uint64_t supported_flags() override;
      
    };
    
  };
  
};

#endif
