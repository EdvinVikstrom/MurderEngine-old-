#ifndef FILE_UTILS_H
  #define FILE_UTILS_H

char* file_utils_read(const std::string &filepath, unsigned int& bufferLength);
void file_utils_write(const std::string &filepath, unsigned int bufferLength, unsigned char* buffer);

#endif
