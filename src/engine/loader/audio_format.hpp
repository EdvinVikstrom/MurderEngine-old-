#ifndef AUDIO_FORMAT_H
  #define AUDIO_FORMAT_H

#include "file_format.h"

namespace me {

  namespace format {

    struct audio_format : file_format {

      AudioFileFormat format;

      audio_format(AudioFileFormat format) : file_format(me::format::FileType::FTYPE_AUDIO)
      {
        this->format = format;
      }

      virtual int load_audio(me::bytebuff &buffer, me::AudioTrack* track, uint64_t flags) = 0;
      virtual bool recognized(me::fileattr &file) = 0;
      virtual std::vector<std::string> get_file_exts() = 0;
      virtual uint64_t supported_flags() = 0;

    };

  };

};

#endif
