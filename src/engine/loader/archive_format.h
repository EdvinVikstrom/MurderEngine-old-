#ifndef ARCHIVE_FORMAT_H
  #define ARCHIVE_FORMAT_H

#include "file_format.h"

namespace me {

  namespace format {

    struct archive_format : file_format {

      ArchiveFileFormat format;

      archive_format(ArchiveFileFormat format) : file_format(FTYPE_ARCHIVE)
      {
        this->format = format;
      }

      virtual int load_archive(me::bytebuff &buffer, me::Archive* archive, uint64_t flags) = 0;
      virtual int write_archive(me::bytebuff &buffer, me::Archive* archive, uint64_t flags) = 0;
      virtual bool recognized(me::fileattr &file) = 0;
      virtual std::vector<std::string> get_file_exts() = 0;
      virtual uint64_t supported_flags() = 0;

    };

  };

};

#endif
