#ifndef FILE_UTILS_H
  #define FILE_UTILS_H

char* file_utils_read(const char* filepath, unsigned int& bufferLength);
void file_utils_write(const char* filepath, unsigned int bufferLength, unsigned char* buffer);

#endif
