#include <iostream>
//#include <ofstream>
#include <fstream>
#include "FileUtils.h"
#include "Logger.h"

extern me::log* ME_LOGGER;

char* file_utils_read(const char* filepath, unsigned int& bufferLength)
{
  std::streampos size;
  std::ifstream file(filepath, std::ios::in|std::ios::binary|std::ios::ate);
  if (file.is_open())
  {
    ME_LOGGER->out("Reading file\n");

    size = file.tellg();
    bufferLength = (unsigned int) size;
    char* data = new char[size];

    file.seekg(0, std::ios::beg);
    file.read(data, size);
    file.close();
    return data;
  }else
  ME_LOGGER->err("Can't open\n");
  return nullptr;
}
void file_utils_write(const char* filepath, unsigned int bufferLength, unsigned char* buffer)
{

}
