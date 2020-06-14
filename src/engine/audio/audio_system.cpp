#include "audio_system.hpp"
#include "../kernel/common.hpp"
#include "../../external/portaudio/include/portaudio.h"

#include <iostream>
#include <vector>
#include <map>

#define FRAMES_PER_BUFFER                 1L

static std::map<uint32_t, me::AudioTrack*> tracks;
static std::map<uint32_t, PaStream*> streams;

static int pa_callback(const void *inputBuffer, void *outputBuffer,
unsigned long framesPerBuffer,
const PaStreamCallbackTimeInfo* timeInfo,
PaStreamCallbackFlags statusFlags,
void *userData)
{
  me::AudioTrack* track = (me::AudioTrack*) userData;
  if (!track->state.playing)
  return 0;

  uint32_t* out = (uint32_t*) outputBuffer;
  unsigned char* bytes = (unsigned char*) track->waveform->bytes;
  for(uint32_t i = 0; i < framesPerBuffer; i++)
  {
    for (unsigned char j = 0; j < 2; j++)
    {
      uint32_t audio;
      if (track->info.format == me::AudioFormat::ME_AUD_FORMAT_S8BIT_PCM) audio = bytes[track->state.position++];
      else if (track->info.format == me::AudioFormat::ME_AUD_FORMAT_S16BIT_PCM) audio = (bytes[track->state.position++]) | (bytes[track->state.position++] << 8);
      else if (track->info.format == me::AudioFormat::ME_AUD_FORMAT_S24BIT_PCM) audio = (bytes[track->state.position++]) | (bytes[track->state.position++] << 8) | (bytes[track->state.position++] << 16);
      else if (track->info.format == me::AudioFormat::ME_AUD_FORMAT_S32BIT_PCM) audio = (bytes[track->state.position++]) | (bytes[track->state.position++] << 8) | (bytes[track->state.position++] << 16) | (bytes[track->state.position++] << 24);
      else if (track->info.format == me::AudioFormat::ME_AUD_FORMAT_FLOAT32) audio = 0;
      out[j] = audio * track->state.gain;
    }
  }
  return 0;
}

int me::audio::init()
{
  PaError err = Pa_Initialize();
  if (err != paNoError)
  {
    std::cout << "[AudioSystem] Failed to initialize [PortAudio]\n";
    return ME_ERR;
  }
  return ME_FINE;
}

int me::audio::cleanup()
{
  PaError err = Pa_Terminate();
  if (err != paNoError)
  {
    std::cout << "[AudioSystem] Failed to terminate [PortAudio]\n";
    return ME_ERR;
  }
  return ME_FINE;
}

uint32_t me::audio::register_track(me::AudioTrack* track)
{
  uint32_t track_id = tracks.size();
  tracks[track_id] = track;
  return track_id;
}

int me::audio::load_track(uint32_t track_id)
{
  me::AudioTrack* track = tracks[track_id];
  PaSampleFormat format;
  if (track->info.format == ME_AUD_FORMAT_S8BIT_PCM) format = paInt8;
  else if (track->info.format == ME_AUD_FORMAT_S16BIT_PCM) format = paInt16;
  else if (track->info.format == ME_AUD_FORMAT_S24BIT_PCM) format = paInt24;
  else if (track->info.format == ME_AUD_FORMAT_S32BIT_PCM) format = paInt32;
  else if (track->info.format == ME_AUD_FORMAT_U8BIT_PCM) format = paUInt8;
  else if (track->info.format == ME_AUD_FORMAT_FLOAT32) format = paFloat32;
  else if (track->info.format == ME_AUD_FORMAT_FLOAT64)
  {
    std::cout << "[AudioSystem] { format: FLOAT64 } not supported\n";
    return ME_ERR;
  }
  PaStream* stream;
  PaError err = Pa_OpenDefaultStream(
  &stream,
  0,
  track->info.channels,
  format,
  track->info.sampleRate,
  FRAMES_PER_BUFFER,
  pa_callback,
  track
  );
  if (err != paNoError)
  {
    std::cout << "[AudioSystem] Failed to load AudioTrack\n";
    return ME_ERR;
  }
  streams[track_id] = stream;
  return ME_FINE;
}

int me::audio::play_track(uint32_t track_id)
{
  me::AudioTrack* track = tracks[track_id];
  track->state.playing = true;
  PaStream* stream = streams[track_id];
  PaError err = Pa_StartStream(stream);
  if (err != paNoError)
  {
    std::cout << "[AudioSystem] Failed to play track\n";
    return ME_ERR;
  }
  return ME_FINE;
}

int me::audio::stop_track(uint32_t track_id)
{
  me::AudioTrack* track = tracks[track_id];
  track->state.playing = false;
  PaStream* stream = streams[track_id];
  PaError err = Pa_StopStream(stream);
  if (err != paNoError)
  {
    std::cout << "[AudioSystem] Failed to stop track\n";
    return ME_ERR;
  }
  return ME_FINE;
}
