#ifndef OBJ_READER_H
  #define OBJ_READER_H

#include "../../mesh_reader.h"

namespace me {

  namespace fformat {

    class obj_reader : public mesh_reader {

    public:

      int read_obj(me::file_state &file, me::scene_packet* scene);
      int read_mesh(me::file_state &file, me::scene_packet* scene) override
      {
        return read_obj(file, scene);
      }
      bool recognized(me::file_state &file) override;
      std::vector<std::string> get_file_exts() override;

    };

  };

};

#endif
