#include "wave_format.h"

int me::format::wave_format::load_audio(me::fileattr &file, me::AudioTrack* track)
{
  file.readFile();
  wave_header header;
  header.riff.chunkID = file.buffer->pull_uint32();
  header.riff.chunkSize = file.buffer->pull_uint32();
  header.riff.format = file.buffer->pull_uint32();

  header.fmt.subChunkID = file.buffer->pull_uint32();
  header.fmt.subChunkSize = file.buffer->pull_uint32();
  header.fmt.format = file.buffer->pull_uint16();
  header.fmt.channels = file.buffer->pull_uint16();
  header.fmt.sampleRate = file.buffer->pull_uint32();
  header.fmt.byteRate = file.buffer->pull_uint32();
  header.fmt.blockAlign = file.buffer->pull_uint16();
  header.fmt.bitsPerSample = file.buffer->pull_uint16();

  header.data.subChunkID = file.buffer->pull_uint32();
  header.data.subChunkSize = file.buffer->pull_uint32();

  if (header.fmt.bitsPerSample == 8)
    track->info.format = AudioFormat::ME_AUD_FORMAT_S8BIT_PCM;
  else if (header.fmt.bitsPerSample == 16)
    track->info.format = AudioFormat::ME_AUD_FORMAT_S16BIT_PCM;
  else if (header.fmt.bitsPerSample == 24)
    track->info.format = AudioFormat::ME_AUD_FORMAT_S24BIT_PCM;
  else if (header.fmt.bitsPerSample == 32)
    track->info.format = AudioFormat::ME_AUD_FORMAT_S32BIT_PCM;
  track->info.sampleRate = header.fmt.sampleRate;
  track->info.channels = header.fmt.channels;

  track->info.source = file.filepath;
  track->info.identifier = file.filepath;

  std::cout <<
  "[WaveFormat]: sampleRate: " << header.fmt.sampleRate <<
  " | byteRate: " << header.fmt.byteRate <<
  " | bitsPerSample: " << header.fmt.bitsPerSample <<
  " | channels: " << header.fmt.channels <<
  " | format: " << (header.fmt.format == 1 ? "PCM" : "Compression") << "\n";

  uint32_t size = file.buffer->length - 52;
  track->waveform = new AudioWave(size);
  for (uint32_t i = 0; i < size; i++)
    track->waveform->bytes[i] = file.buffer->data[i];
  return ME_FINE;
}

bool me::format::wave_format::recognized(me::fileattr &file)
{
  return me::str_ends(file.filepath, ".wav") || me::str_ends(file.filepath, ".wave");
}

std::vector<std::string> me::format::wave_format::get_file_exts()
{
  return { "wav", "wave" };
}
