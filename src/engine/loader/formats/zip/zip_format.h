#ifndef ZIP_FORMAT_H
  #define ZIP_FORMAT_H

#include "../../archive_format.h"

namespace me {

  namespace format {

    enum zip_general_purpose_flag {
      ENCRYPTED_FILE = 1,
      COMPRESSION_OPTION1 = 2,
      COMPRESSION_OPTION2 = 4,
      DATA_DESCRIPTOR = 8,
      ENHANCED_DEFLATION = 16,
      COMPRESSED_PATCHED_DATA = 32,
      STRONG_ENCRYPTION = 64,

      LANG_ENCODING = 2048,
      MASK_HEADER_VALUES = 8192
    };

    enum zip_compression_method : unsigned short {
      ZIP_COMPRESSION_NONE = 0,
      ZIP_COMPRESSION_SHRUNK = 1,
      ZIP_COMPRESSION_REDUCED_WIDTH_FAC1 = 2,
      ZIP_COMPRESSION_REDUCED_WIDTH_FAC2 = 3,
      ZIP_COMPRESSION_REDUCED_WIDTH_FAC3 = 4,
      ZIP_COMPRESSION_REDUCED_WIDTH_FAC4 = 5,
      ZIP_COMPRESSION_IMPLODED = 6,
      ZIP_COMPRESSION_DEFLATED = 8,
      ZIP_COMPRESSION_ENHANCED_DEFLATED = 9,
      ZIP_COMPRESSION_PKWARE_DCL = 10,
      ZIP_COMPRESSION_BZIP2 = 12,
      ZIP_COMPRESSION_LZMA = 14,
      ZIP_COMPRESSION_IBM_TERSE = 18,
      ZIP_COMPRESSION_IBM = 19,
      ZIP_COMPRESSION_PPMD = 98
    };

    struct zip_data_descriptor {
      uint32_t signature;
      uint32_t CRC32;
      uint32_t compressedSize;
      uint32_t uncompressedSize;
    };

    struct zip_local_header {
      uint32_t signature;
      uint16_t minVersion;
      uint16_t flag;
      uint16_t compressionMethod;
      uint16_t lastModificationTime;
      uint16_t lastModificationDate;
      uint32_t CRC32;
      uint32_t compressedSize;
      uint32_t uncompressedSize;
      uint16_t fileNameLength;
      uint16_t extraFieldLength;
      uint8_t* fileName;
      uint8_t* extraField;
    };

    struct zip_file {
      zip_local_header header;
      uint8_t* data;
      zip_data_descriptor descriptor;

    };

    struct zip_struct {
      std::vector<zip_file*> files;
    };

    struct zip_format : archive_format {

      zip_format() : archive_format(AFF_ZIP) { }

      int next_file(me::bytebuff &buffer, zip_file &file);

      int load_archive(me::bytebuff &buffer, me::Archive* archive, uint64_t flags) override;
      int write_archive(me::bytebuff &buffer, me::Archive* archive, uint64_t flags) override;
      bool recognized(me::fileattr &file) override;
      std::vector<std::string> get_file_exts() override;
      uint64_t supported_flags() override;

    };

  };

};

#endif
