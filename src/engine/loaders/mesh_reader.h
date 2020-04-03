#ifndef MESH_LOADER_H
  #define MESH_LOADER_H

#include "file_format.h"

namespace me {

  namespace fformat {

    class mesh_reader : public file_format {

    public:

      mesh_reader() : file_format(me::fformat::format_type::MESH) { }

      virtual int read_mesh(me::file_state &file, scene_packet* scene) = 0;
      inline int read_file(me::file_state &file, scene_packet* scene)
      {
        int result = read_mesh(file, scene);
        if (result != ME_FINE)
          return result;
        return ME_FINE;
      }

      virtual bool recognized(me::file_state &file) = 0;
      virtual std::vector<std::string> get_file_exts() = 0;

    };

    void load_mesh(me::mesh* mesh, int usage);

  };


};

#endif
