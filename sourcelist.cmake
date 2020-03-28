set(SOURCES ${SOURCES}
  ${SOURCE_DIR}/Main.cpp
  ${SOURCE_DIR}/engine/EngineManager.cpp
  ${SOURCE_DIR}/engine/MurderEngine.cpp
  ${SOURCE_DIR}/engine/utilities/FileUtils.cpp
  ${SOURCE_DIR}/engine/utilities/Logger.cpp
  ${SOURCE_DIR}/engine/utilities/StringUtils.cpp
  ${SOURCE_DIR}/engine/utilities/ArrayUtils.cpp
  ${SOURCE_DIR}/engine/utilities/TimeUtils.cpp
  ${SOURCE_DIR}/engine/loaders/parsers/collada_parser.cpp
  ${SOURCE_DIR}/engine/loaders/ImageReader.cpp
  ${SOURCE_DIR}/engine/loaders/mesh_loader.cpp
  ${SOURCE_DIR}/engine/loaders/shader_loader.cpp
  ${SOURCE_DIR}/engine/math/vectors.cpp
  ${SOURCE_DIR}/engine/math/maths.cpp
  ${SOURCE_DIR}/engine/scene/scene.cpp
  ${SOURCE_DIR}/engine/scene/texture.cpp
  ${SOURCE_DIR}/engine/scene/particle/particle.cpp
  ${SOURCE_DIR}/engine/scene/scenes/scene_2d_viewport.cpp
  ${SOURCE_DIR}/engine/scene/scenes/scene_outliner.cpp
  ${SOURCE_DIR}/engine/renderer/vulkan_api.cpp
  ${SOURCE_DIR}/engine/renderer/opengl_api.cpp
)
set(HEADERS ${HEADERS}
)
