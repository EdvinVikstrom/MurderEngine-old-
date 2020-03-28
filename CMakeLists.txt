cmake_minimum_required(VERSION 3.10)

project(MurderEngine)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(/usr/include/)
link_directories(${SOURCE_DIR}/external/vulkan/x86_64/lib)
link_directories(/usr/lib/)

include(sourcelist.cmake)
add_executable(MurderEngine ${HEADERS} ${SOURCES})
target_link_libraries(MurderEngine glfw GLEW GL GLU vulkan)
