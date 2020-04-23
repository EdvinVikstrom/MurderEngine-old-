add_subdirectory(utilities)
add_subdirectory(simulation)
add_subdirectory(scene)
add_subdirectory(renderer)
add_subdirectory(math)
add_subdirectory(loader)
add_subdirectory(kernel)
add_subdirectory(audio)

set(SRC
  ${SRC}
  ${CMAKE_CURRENT_SOURCE_DIR}/MurderEngine.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/EngineInit.cpp
  PARENT_SCOPE
)
