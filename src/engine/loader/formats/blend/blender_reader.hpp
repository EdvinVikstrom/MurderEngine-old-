#ifndef BLENDER_READER_H
  #define BLENDER_READER_H

#include "../../mesh_reader.hpp"

namespace me {
  
  namespace fformat {
    
    class blender_reader : public mesh_reader {
      
      public:
      
      int read_blender(me::file_state &file, me::scene_packet* scene);
      int read_mesh(me::file_state &file, me::scene_packet* scene) override
      {
        return read_blender(file, scene);
      }
      bool recognized(me::file_state &file) override;
      std::vector<std::string> get_file_exts() override;
      
    };
    
  };
  
};

#endif
