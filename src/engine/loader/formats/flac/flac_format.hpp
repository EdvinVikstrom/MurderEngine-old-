#ifndef FLAC_FORMAT_H
  #define FLAC_FORMAT_H

#include "../../audio_format.hpp"

namespace me {

  namespace format {

    struct flac_header {

      uint32_t signature;

      struct metadata_stream_info {
        uint16_t min_blockSize; // 16 bit
        uint16_t max_blockSize; // 16 bit
        uint32_t min_frameSize; // 24 bit
        uint32_t max_frameSize; // 24 bit

        uint32_t sampleRate; // 20 bit
        uint8_t channels; // 3 bit
        uint8_t bitsPerSample; // 5 bit
        uint64_t nSamples; // 36 bit
        uint8_t* md5Signature; // 128 bit
      } stream_info;

      struct metadata_padding {
        uint8_t* nBits; // n * 8
      } padding;

      struct metadata_application {
        uint32_t appId; // 32 bit
        uint8_t* appData; // n * 8
      } app;

      struct metadata_seektable {
        struct seekpoint {
          uint64_t sampleNumber; // 64 bit
          uint64_t offset; // 64 bit
          uint16_t nSamples; // 16 bit
        };
        std::vector<seekpoint> seekpoints;
      } seektable;

    };

    struct flac_format : audio_format {

      flac_format() : audio_format(AFF_FLAC) { }

      int load_audio(me::bytebuff &buffer, me::AudioTrack* track, uint64_t flags) override;
      bool recognized(me::fileattr &file) override;
      std::vector<std::string> get_file_exts() override;
      uint64_t supported_flags() override;

    };

  };

};

#endif