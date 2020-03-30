#ifndef IMAGE_READER_H
  #define IMAGE_READER_H

#define ME_TEX_FORMAT_RGBA8                  0x1238
#define ME_TEX_FORMAT_RGBA16                 0x12316
#define ME_TEX_FORMAT_RGBA24                 0x12324
#define ME_TEX_FORMAT_RGBA32                 0x12332
#define ME_TEX_FORMAT_RGB8                   0x128
#define ME_TEX_FORMAT_RGB16                  0x1216
#define ME_TEX_FORMAT_RGB24                  0x1224
#define ME_TEX_FORMAT_RGB32                  0x1232
#define ME_TEX_FORMAT_GRAY4                  0x18
#define ME_TEX_FORMAT_GRAY8                  0x18
#define ME_TEX_FORMAT_GRAY16                 0x116
#define ME_TEX_FORMAT_GRAY24                 0x124
#define ME_TEX_FORMAT_GRAY32                 0x132
#define ME_TEX_FORMAT_BINARY                 0x11

namespace me {

  namespace fformat {

    class image_reader : public file_format {

    public:

      image_reader() : file_format(me::fformat::format_type.IMAGE) { }

      virtual int read_image(const std::string &file_name, unsigned char* data, uint32_t data_size, me::image* image) = 0;
      inline int read_file(const std::string &file_name, unsigned char* data, uint32_t data_size, me::image* image) override
      {
        image = new me::image;
        int result = read_image(file_name, data, data_size, image);
        if (result != ME_FINE)
          return result;
        return ME_FINE;
      }

      virtual bool recognized(const std::string &file_name, unsigned char* data, uint32_t data_size) = 0;
      virtual std::vector<std::string> get_file_exts() = 0;

    };

  };

};

#endif
