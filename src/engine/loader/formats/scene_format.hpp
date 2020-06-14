#ifndef SCENE_FORMAT_HPP
  #define SCENE_FORMAT_HPP

#include "../../scene/scene.hpp"
#include "../../kernel/io/filebuff.hpp"
#include "file_format.hpp"

namespace me {

  namespace format {

    enum MeshFormat {
      MESH_FORMAT_VNTC,
      MESH_FORMAT_VERTEX
    };

    struct SceneFormat {

      me::format::SceneFileFormat format;

      SceneFormat(me::format::SceneFileFormat format)
      {
        this->format = format;
      }

      virtual int readScene(me::bytebuff &buffer, Scene* scene, uint64_t flags) = 0;
      virtual int writeScene(me::bytebuff &buffer, Scene* scene, uint64_t flags) = 0;
      virtual bool recognized(me::filebuff* file) = 0;
      virtual std::vector<std::string> getFileExts() = 0;
      virtual uint64_t supportedFlags() = 0;

    };

    void initSceneFormats();
    void cleanupSceneFormats();

  };

  namespace reader {

    int readScene(const std::string &filepath, me::Scene* scene, uint64_t flags);
    int readScene(me::bytebuff* buffer, me::format::SceneFileFormat format, me::Scene* scene, uint64_t flags);

  };

  namespace writer {

    int writeScene(me::bytebuff* buffer, me::format::SceneFileFormat format, me::Scene* scene, uint64_t flags);

  };


};

#endif
