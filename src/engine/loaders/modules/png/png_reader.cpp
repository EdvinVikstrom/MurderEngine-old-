#include "png_reader.h"
#include "../../../../external/libpng/png.h"

int me::fformat::png_reader::read_image(me::fileattr &file, me::image* image)
{
  // TODO: error handling
  png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  png_infop info_ptr = png_create_info_struct(png_ptr);

  if(setjmp(png_jmpbuf(png_ptr)))
  {
    std::cout << "[PNGLoader] [ERR]\n";
    return ME_ERR;
  }

  /* initialize */
  png_init_io(png_ptr, file.file);
  png_read_info(png_ptr, info_ptr);

  /* image info */
  image->width = png_get_image_width(png_ptr, info_ptr);
  image->height = png_get_image_height(png_ptr, info_ptr);
  image->depth = png_get_bit_depth(png_ptr, info_ptr);
  png_byte colorType = png_get_color_type(png_ptr, info_ptr);
  std::cout << "[PNGLoader]: width: " << image->width << ", height: " << image->height << " | depth: " << image->depth << "\n";

  image->format = ME_TEX_FORMAT_RGB;
  if (colorType == PNG_COLOR_TYPE_RGBA)
    image->format = ME_TEX_FORMAT_RGBA;
  else if (colorType == PNG_COLOR_TYPE_GRAY)
    image->format = ME_TEX_FORMAT_GRAY;

  if (image->depth == 16)
    png_set_strip_16(png_ptr);

  if (colorType == PNG_COLOR_TYPE_PALETTE)
    png_set_palette_to_rgb(png_ptr);
  else if (colorType == PNG_COLOR_TYPE_GRAY && image->depth < 8)
    png_set_expand_gray_1_2_4_to_8(png_ptr);

  if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
    png_set_tRNS_to_alpha(png_ptr);

  if (colorType == PNG_COLOR_TYPE_RGB || colorType == PNG_COLOR_TYPE_GRAY || colorType == PNG_COLOR_TYPE_PALETTE)
    png_set_filler(png_ptr, 0xFF, PNG_FILLER_AFTER);

  if (colorType == PNG_COLOR_TYPE_GRAY || colorType == PNG_COLOR_TYPE_GRAY_ALPHA)
    png_set_gray_to_rgb(png_ptr);

  png_read_update_info(png_ptr, info_ptr);

  png_bytep* pointers = new png_bytep[image->height];
  for (uint32_t i = 0; i < image->height; i++)
    pointers[i] = (png_byte*) malloc(png_get_rowbytes(png_ptr,info_ptr));
  png_read_image(png_ptr, pointers);
  file.closeFile();
  if (png_ptr && info_ptr)
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);

  /* process PNG */
  image->pixels = new unsigned char[image->width * image->height * image->format];
  uint32_t index = 0;
  for (uint32_t y = 0; y < image->height; y++)
  {
    png_bytep ptr = pointers[y];
    for (uint32_t x = 0; x < image->width; x++)
    {
      png_bytep pixel = &(ptr[x * 4]);
      if (image->format >= 1) image->pixels[index] = pixel[0];
      if (image->format >= 2) image->pixels[index+1] = pixel[1];
      if (image->format >= 3) image->pixels[index+2] = pixel[2];
      if (image->format >= 4) image->pixels[index+3] = pixel[3];
      index+=image->format;
    }
  }

  return ME_FINE;
}

bool me::fformat::png_reader::recognized(me::fileattr &file)
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

std::vector<std::string> me::fformat::png_reader::get_file_exts()
{
  return { "png" };
}
