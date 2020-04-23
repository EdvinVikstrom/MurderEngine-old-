#ifndef FILE_FORMAT_H
  #define FILE_FORMAT_H

#include "../MurderEngine.h"
#include "../kernel/io/file_reader.h"
#include "../scene/scene_content.h"
#include "../audio/audio.h"
#include <vector>

namespace me {

  namespace format {

    enum FileType {
      FTYPE_INSTANCE = 0,
      FTYPE_IMAGE = 1,
      FTYPE_SCENE = 2,
      FTYPE_AUDIO = 3
    };

    enum ImageFileFormat {
      IFF_PNG,
      IFF_JPEG,
      IFF_GIF,
      IFF_TIFF,
      IFF_BMP,
      IFF_EXR,
      IFF_HDR,
      IFF_RAW
    };

    enum AudioFileFormat {
      AFF_FLAC,
      AFF_ALAC,
      AFF_WAVE,
      AFF_MP3,
      AFF_OGG,
      AFF_RAW
    };

    enum SceneFileFormat {
      SFF_COLLADA,
      SFF_WAVEFRONT,
      SFF_STANFORD,
      SFF_STL,
      SFF_FBX,
      SFF_USD
    };

    struct file_format {

      me::format::FileType type;

      file_format(me::format::FileType type)
      {
        this->type = type;
      }

      virtual bool recognized(me::fileattr &file) = 0;
      virtual std::vector<std::string> get_file_exts() = 0;

    };

    void loadInstance(MeInstance* instance, const std::string &filepath, std::vector<int> flags);
    void loadImage(MeInstance* instance, const std::string &filepath, me::Image* image);
    void loadAudio(MeInstance* instance, const std::string &filepath, me::AudioTrack* track);
    void loadScene(MeInstance* instance, const std::string &filepath, me::ScenePacket* packet);

    void writeImage(MeInstance* instance, const std::string &filepath, me::format::ImageFileFormat image_format, me::Image* image);

    unsigned char* loadRAWData(MeInstance* instance, const std::string &filepath, uint32_t &length);

    void init();
    void cleanup();

  };

};

#endif
