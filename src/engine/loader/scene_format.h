#ifndef MESH_LOADER_H
  #define MESH_LOADER_H

#include "file_format.h"

namespace me {

  namespace format {

    enum SceneFileFormat {
      SFF_COLLADA,
      SFF_WAVEFRONT,
      SFF_STANFORD,
      SFF_STL,
      SFF_FBX,
      SFF_USD
    };

    enum MeshFormat {
      MESH_FORMAT_VNTC,
      MESH_FORMAT_VERTEX
    };

    struct scene_format : file_format {

      SceneFileFormat format;

      scene_format(SceneFileFormat format) : file_format(me::format::FileType::FTYPE_SCENE)
      {
        this->format = format;
      }

      virtual int load_scene(me::fileattr &file, ScenePacket* scene) = 0;
      virtual bool recognized(me::fileattr &file) = 0;
      virtual std::vector<std::string> get_file_exts() = 0;

    };

    void formatMesh(me::Mesh* mesh, MeshFormat format);

  };


};

#endif
