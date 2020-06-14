#ifndef AUDIO_H
  #define AUDIO_H

#include "../scene/metadata.hpp"
#include <string>
#include <map>

namespace me {
  
  enum AudioFormat {
    /* signed */
    ME_AUD_FORMAT_S8BIT_PCM =             0x0,
    ME_AUD_FORMAT_S16BIT_PCM =            0x1,
    ME_AUD_FORMAT_S24BIT_PCM =            0x2,
    ME_AUD_FORMAT_S32BIT_PCM =            0x3,
    
    /* unsigned */
    ME_AUD_FORMAT_U8BIT_PCM =             0x4,
    
    /* float */
    ME_AUD_FORMAT_FLOAT32 =               0x5,
    ME_AUD_FORMAT_FLOAT64 =               0x6
  };
  
  struct AudioWave {
    uint32_t length;
    unsigned char* bytes;
    
    AudioWave(uint32_t length, unsigned char* bytes)
    {
      this->length = length;
      this->bytes = bytes;
    }
    
    AudioWave(uint32_t length)
    {
      this->length = length;
      bytes = new unsigned char[length];
    }
    
    AudioWave() { }
    
    ~AudioWave()
    {
      delete[] bytes;
    }
    
  };
  
  struct AudioInfo {
    uint32_t trackId;
    std::string source;
    std::string identifier;
    me::metadata* metadata;
    
    AudioFormat format;
    double sampleRate;
    unsigned char channels;
  };
  
  struct AudioState {
    uint32_t position = 0;
    bool playing = false;
    
    float gain = 1.0F;
    
  };
  
  struct AudioTrack {
    
    AudioWave* waveform;
    AudioInfo info;
    AudioState state;
    
    AudioTrack(AudioWave* waveform, AudioInfo info, AudioState state)
    {
      this->waveform = waveform;
      this->info = info;
      this->state = state;
    }
    
    AudioTrack() { }
    
    ~AudioTrack()
    {
    }
    
  };
  
};

#endif
