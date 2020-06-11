#ifndef AUDIO_SYSTEM_H
  #define AUDIO_SYSTEM_H

#include "audio.hpp"

namespace me {

  namespace audio {

    int init();
    int cleanup();

    uint32_t register_track(me::AudioTrack* track);
    int load_track(uint32_t track_id);
    int play_track(uint32_t track_id);
    int stop_track(uint32_t track_id);

  };

};

#endif