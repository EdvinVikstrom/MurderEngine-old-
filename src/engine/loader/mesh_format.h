#ifndef MESH_LOADER_H
  #define MESH_LOADER_H

#include "file_format.h"

namespace me {

  namespace format {

    enum MeshFormat {
      MESH_FORMAT_VNTC,
      MESH_FORMAT_VERTEX
    };

    struct mesh_format : public file_format {

    public:

      mesh_format() : file_format(me::format::FileType::FTYPE_MESH) { }

      virtual int read_mesh(me::fileattr &file, scene_packet* scene) = 0;
      inline int read_file(me::fileattr &file, scene_packet* scene)
      {
        int result = read_mesh(file, scene);
        if (result != ME_FINE)
          return result;
        return ME_FINE;
      }

      virtual bool recognized(me::fileattr &file) = 0;
      virtual std::vector<std::string> get_file_exts() = 0;

    };

    void formatMesh(me::mesh* mesh, MeshFormat format);

  };


};

#endif
