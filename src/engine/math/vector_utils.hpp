#ifndef VECTOR_UTILS_H
  #define VECTOR_UTILS_H

#include "../kernel/kernel.hpp"
#include "vectors.hpp"
#include <vector>

namespace me {

  namespace utils {

    /* NOTE: the `size` is the float array length */
    bool float_to_vec2_array(uint32_t size, float* array, std::vector<me::vec2> &vectors, bool allocate);
    bool float_to_vec3_array(uint32_t size, float* array, std::vector<me::vec3> &vectors, bool allocate);
    bool float_to_vec4_array(uint32_t size, float* array, std::vector<me::vec4> &vectors, bool allocate);

    /* NOTE: the `vectors` pointer must be allocated */
    bool float_to_vec2_array(uint32_t size, float* array, me::vec2* vectors, bool allocate);
    bool float_to_vec3_array(uint32_t size, float* array, me::vec3* vectors, bool allocate);
    bool float_to_vec4_array(uint32_t size, float* array, me::vec4* vectors, bool allocate);

  };

};

#endif