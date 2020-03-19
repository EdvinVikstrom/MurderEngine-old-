#ifndef IMAGE_READER_H
  #define IMAGE_READER_H

namespace me {

  unsigned int createImageId(me::image* image);
  me::image* loadImage(const char* path, unsigned int format);
  me::image* loadImage(const char* path);
  void initImageReader();

};

#endif
