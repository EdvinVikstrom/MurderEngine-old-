#include <iostream>
//#include <ofstream>
#include <fstream>
#include "FileUtils.h"
#include "Logger.h"

me::log* FILE_LOGGER = new me::log("FileReader", "\e[30m;1m[%N] %T #%M \e[0m");

char* file_utils_read(const std::string &filepath, unsigned int& bufferLength)
{
  std::streampos size;
  std::ifstream file(filepath, std::ios::in|std::ios::binary|std::ios::ate);
  if (file.is_open())
  {
    FILE_LOGGER->out(std::string("Reading file \"") + filepath + "\"\n");

    size = file.tellg();
    bufferLength = (unsigned int) size;
    char* data = new char[size];

    file.seekg(0, std::ios::beg);
    file.read(data, size);
    file.close();
    return data;
  }else
    FILE_LOGGER->out(std::string("Can't open file \"") + filepath + "\"\n");
  return nullptr;
}
void file_utils_write(const std::string &filepath, unsigned int bufferLength, unsigned char* buffer)
{

}
