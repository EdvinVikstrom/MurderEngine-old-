#include "vector_utils.hpp"

bool me::utils::float_to_vec2_array(uint32_t size, float* array, std::vector<me::vec2> &vectors, bool allocate)
{
  if (size < 2) return false;
  if (allocate) vectors.reserve(size / 2);
  for (uint32_t i = 0; i < size; i+=2)
  vectors.emplace_back(array[i], array[i+1]);
  return true;
}
bool me::utils::float_to_vec3_array(uint32_t size, float* array, std::vector<me::vec3> &vectors, bool allocate)
{
  if (size < 3) return false;
  if (allocate) vectors.reserve(size / 3);
  for (uint32_t i = 0; i < size; i+=3)
  vectors.emplace_back(array[i], array[i+1], array[i+2]);
  return true;
}
bool me::utils::float_to_vec4_array(uint32_t size, float* array, std::vector<me::vec4> &vectors, bool allocate)
{
  if (size < 4) return false;
  if (allocate) vectors.reserve(size / 4);
  for (uint32_t i = 0; i < size; i+=4)
  vectors.emplace_back(array[i], array[i+1], array[i+2], array[i+3]);
  return true;
}

bool me::utils::float_to_vec2_array(uint32_t size, float* array, me::vec2* vectors, bool allocate)
{
  if (size < 2) return false;
  if (allocate) vectors = new me::vec2[size / 2];
  for (uint32_t i = 0; i < size; i+=2)
  vectors[i / 2] = {array[i], array[i+1]};
  return true;
}
bool me::utils::float_to_vec3_array(uint32_t size, float* array, me::vec3* vectors, bool allocate)
{
  if (size < 3) return false;
  if (allocate) vectors = new me::vec3[size / 3];
  for (uint32_t i = 0; i < size; i+=3)
  vectors[i / 3] = {array[i], array[i+1], array[i+2]};
  return true;
}
bool me::utils::float_to_vec4_array(uint32_t size, float* array, me::vec4* vectors, bool allocate)
{
  if (size < 4) return false;
  if (allocate) vectors = new me::vec4[size / 4];
  for (uint32_t i = 0; i < size; i+=4)
  vectors[i / 4] = {array[i], array[i+1], array[i+2], array[i+3]};
  return true;
}
