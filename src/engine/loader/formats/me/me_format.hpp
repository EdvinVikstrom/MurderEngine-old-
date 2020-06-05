#ifndef ME_WRITER_H
  #define ME_WRITER_H

#include "../../file_format.h"
#include "../../../MurderEngine.h"

namespace me {

  namespace format {

    enum MEWFlags {
      MEWF_MESHES = 0,
      MEWF_IMAGES = 1,
      MEWF_LIGHTS = 2,
      MEWF_CAMERAS = 3,
      MEWF_MATERIALS = 4,
      MEWF_SCRIPTS = 5,
      MEWF_SETTINGS = 6,
      MEWF_PROPERITES = 7
    };

    struct me_format : file_format {

      me_format() : file_format(FileType::FTYPE_INSTANCE) { }

      void write_file(me::fileattr &file, MeInstance* instance, std::vector<MEWFlags> flags);

      bool recognized(me::fileattr &file) override;
      std::vector<std::string> get_file_exts() override;

    };

  };

};

#endif
