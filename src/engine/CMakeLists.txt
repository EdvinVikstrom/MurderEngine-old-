set(SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/MurderEngine.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/EngineInit.cpp
)

add_subdirectory(utilities)
add_subdirectory(simulation)
add_subdirectory(scene)
add_subdirectory(renderer)
add_subdirectory(math)
add_subdirectory(loader)
add_subdirectory(kernel)
