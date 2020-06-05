#ifndef TIFFLZW_DECOMPRESSOR
  #define TIFFLZW_DECOMPRESSOR

#define LZW_EOI_CODE          257
#define LZW_CLEAR_CODE        256
#define LZW_FIRST_CODE        258

namespace me {

  namespace tiff {

    struct lzw : me::format::tiff_decompressor {

      std::string* string_table;
      uint32_t table_index;
      uint32_t bits_to_get;
      uint32_t image_size;
      uint32_t position;

      lzw(me::bytebuff* inputStream, me::Image* image) : tiff_decompressor(inputStream, image)
      {
        table_index = 0;
        bits_to_get = 0;
        image_size = image->bitmap->width * image->bitmap->height * ((image->bitmap->bitsPerSample / 8) * image->info.format & 0x00FF);
        position = 0;
      }

      uint32_t next_code()
      {
        return inputStream->pull_uint(bits_to_get);
      }

      void init_string_table()
      {
        string_table = new std::string[4096];
        for (uint16_t i = 0; i < 256; ++i)
        {
          string_table[i] = std::string(new char[1]{(char) i}, 1);
        }
        table_index = 258;
        bits_to_get = 9;
      }

      void write_string(std::string &string)
      {
        if (position < image_size)
        {
          uint32_t max_index = me::maths::min((uint32_t) string.size(), image_size - position);
          for (uint32_t i = 0; i < max_index; ++i)
            image->bitmap->map[position++] = string.at(i);
        }
      }

      void add_string_to_table(std::string &old_string, char new_string)
      {
        std::string string(old_string + new_string, old_string.size() + 1);
        string_table[table_index++] = string;
        if (table_index == 511)
          bits_to_get = 10;
        else if (table_index == 1023)
          bits_to_get = 11;
        else if (table_index == 2047)
          bits_to_get = 12;
      }

      void add_string_to_table(std::string &string)
      {
        string_table[table_index++] = string;
        if (table_index == 511)
          bits_to_get = 10;
        else if (table_index == 1023)
          bits_to_get = 11;
        else if (table_index == 2047)
          bits_to_get = 12;
      }

      int decode() override
      {
        init_string_table();
        uint32_t old_code = 0;
        uint32_t code = 0;
        while((code = next_code()) != LZW_EOI_CODE)
        {
          if (code == LZW_CLEAR_CODE)
          {
            init_string_table();
            code = next_code();
            if (code == LZW_EOI_CODE)
              break;
            write_string(string_table[code]);
            old_code = code;
          }else
          {
            std::string out_string;
            if (code < table_index)
            {
              out_string = string_table[code];
              write_string(out_string);
              add_string_to_table(string_table[old_code], out_string.at(0));
              old_code = code;
            }else
            {
              out_string = string_table[old_code];
              out_string = out_string + out_string.at(0);
              write_string(out_string);
              add_string_to_table(out_string);
              old_code = code;
            }
          }
        }
        std::cout << "DONE!!!\n";
        return ME_FINE;
      }

    };

  };

};

#endif
