cmake_minimum_required(VERSION 3.10)

project(MurderEngine)

# set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(/usr/include/)
link_directories(${SOURCE_DIR}/external/vulkan/x86_64/lib)
link_directories(/usr/lib/)

add_library(libpng SHARED IMPORTED)
set_target_properties(libpng PROPERTIES IMPORTED_LOCATION src/external/libpng/libpng.so)
link_directories(src/external/libpng)
link_directories(src/external/portaudio)

add_subdirectory(src)
message(STATUS "sources: ${SRC}")

set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(MurderEngine ${SRC})

set_property(TARGET MurderEngine PROPERTY CXX_STANDARD 17)
target_link_libraries(MurderEngine glfw GLEW GL GLU vulkan libpng portaudio)
