#include "png_format.h"
#include "../../../../external/libpng/png.h"

int me::format::png_format::load_image(me::fileattr &file, me::Image* image)
{
  // TODO: error handling
  png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
  png_infop info_ptr = png_create_info_struct(png_ptr);

  /* initialize */
  png_init_io(png_ptr, file.file);
  //png_set_sig_bytes(png_ptr, 8);
  png_read_info(png_ptr, info_ptr);

  /* getting the image info */
  image->bitmap->width = png_get_image_width(png_ptr, info_ptr);
  image->bitmap->height = png_get_image_height(png_ptr, info_ptr);
  image->bitmap->depth = png_get_bit_depth(png_ptr, info_ptr);
  png_byte colorType = png_get_color_type(png_ptr, info_ptr);

  /* setting the image format */
  image->info.format = ME_IMG_FORMAT_RGB;
  if (colorType == PNG_COLOR_TYPE_RGBA)
    image->info.format = ME_IMG_FORMAT_RGBA;
  else if (colorType == PNG_COLOR_TYPE_GRAY)
    image->info.format = ME_IMG_FORMAT_GRAY;

  image->bitmap->depth = image->bitmap->depth * (image->info.format & 0x0F);
  std::cout << "[PNGLoader]: width: " << image->bitmap->width << ", height: " << image->bitmap->height << " | depth: " << (int) image->bitmap->depth << "\n";

  /* setting up libpng */
    if (image->bitmap->depth == 16)
      png_set_strip_16(png_ptr);
    if (colorType == PNG_COLOR_TYPE_PALETTE)
      png_set_palette_to_rgb(png_ptr);
    else if (colorType == PNG_COLOR_TYPE_GRAY && image->bitmap->depth < 8)
      png_set_expand_gray_1_2_4_to_8(png_ptr);
    if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
      png_set_tRNS_to_alpha(png_ptr);
    if (colorType == PNG_COLOR_TYPE_RGB || colorType == PNG_COLOR_TYPE_GRAY || colorType == PNG_COLOR_TYPE_PALETTE)
      png_set_filler(png_ptr, 0xFF, PNG_FILLER_AFTER);
    if (colorType == PNG_COLOR_TYPE_GRAY || colorType == PNG_COLOR_TYPE_GRAY_ALPHA)
      png_set_gray_to_rgb(png_ptr);
    png_read_update_info(png_ptr, info_ptr);
  /* ---------------------------------------------- */

  /* read file */
  if(setjmp(png_jmpbuf(png_ptr)))
  {
    std::cout << "[PNGLoader] [ERR]\n";
    return ME_ERR;
  }

  png_bytep* pointers = new png_bytep[image->bitmap->height];
  for (uint32_t i = 0; i < image->bitmap->height; i++)
    pointers[i] = (png_byte*) malloc(png_get_rowbytes(png_ptr,info_ptr));
  png_read_image(png_ptr, pointers);

  /* can explode program */
    file.closeFile();
  /* ------------------- */

  if (png_ptr && info_ptr)
    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);

  /* process PNG */
  std::cout << "crash?\n";
  unsigned short byte_per_pixel = image->bitmap->depth / 8;
  uint32_t image_size = image->bitmap->width * image->bitmap->height * byte_per_pixel;
  std::cout << image_size << " is the size\n";
  image->bitmap->map = new unsigned char[image_size];
  uint32_t index = 0;
  for (uint32_t y = 0; y < image->bitmap->height; y++)
  {
    png_bytep ptr = pointers[y];
    for (uint32_t x = 0; x < image->bitmap->width; x++)
    {
      png_bytep pixel = &(ptr[x * 4]);
      for (uint16_t i = 0; i < byte_per_pixel; i++)
      {
        if (byte_per_pixel >= i+1)
          image->bitmap->map[index] = pixel[i];
        index++;
      }
      std::cout << image->bitmap->height << " h\n";
    }
  }
  return ME_FINE;
}

int me::format::png_format::write_image(me::write_buffer &buffer, me::Image* image)
{
  return ME_FINE;
}

bool me::format::png_format::recognized(me::fileattr &file)
{
  return me::str_ends(file.filepath, ".png") || (
    file.buffer->data[0] == 137 &&
    file.buffer->data[1] == 80 &&
    file.buffer->data[2] == 78 &&
    file.buffer->data[3] == 71 &&
    file.buffer->data[4] == 13 &&
    file.buffer->data[5] == 10 &&
    file.buffer->data[6] == 26 &&
    file.buffer->data[7] == 10
  );
}

std::vector<std::string> me::format::png_format::get_file_exts()
{
  return { "png" };
}
