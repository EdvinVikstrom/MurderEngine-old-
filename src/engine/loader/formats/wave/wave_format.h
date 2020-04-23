#ifndef WAVE_FORMAT_H
  #define WAVE_FORMAT_H

#include "../../audio_format.h"

namespace me {

  namespace format {

    struct wave_header {

      struct riff_header {
        uint32_t chunkID;
        uint32_t chunkSize;
        uint32_t format;
      } riff;

      struct fmt_chunk {
        uint32_t subChunkID;
        uint32_t subChunkSize;
        uint16_t format;
        uint16_t channels;
        uint32_t sampleRate;
        uint32_t byteRate;
        uint16_t blockAlign;
        uint16_t bitsPerSample;
      } fmt;

      struct data_chunk {
        uint32_t subChunkID;
        uint32_t subChunkSize;
      } data;

    };

    struct wave_format : audio_format {

      wave_format() : audio_format(AFF_WAVE) { }

      int load_audio(me::fileattr &file, me::AudioTrack* track) override;
      bool recognized(me::fileattr &file) override;
      std::vector<std::string> get_file_exts() override;

    };

  };

};

#endif
