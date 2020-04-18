#ifndef MESH_LOADER_H
  #define MESH_LOADER_H

#include "file_format.h"

namespace me {

  namespace format {

    enum MeshFormat {
      MESH_FORMAT_VNTC,
      MESH_FORMAT_VERTEX
    };

    struct scene_format : public file_format {

    public:

      scene_format() : file_format(me::format::FileType::FTYPE_SCENE) { }

      virtual int read_scene(me::fileattr &file, ScenePacket* scene) = 0;
      inline int read_file(me::fileattr &file, ScenePacket* scene)
      {
        int result = read_scene(file, scene);
        if (result != ME_FINE)
          return result;
        return ME_FINE;
      }

      virtual bool recognized(me::fileattr &file) = 0;
      virtual std::vector<std::string> get_file_exts() = 0;

    };

    void formatMesh(me::Mesh* mesh, MeshFormat format);

  };


};

#endif
