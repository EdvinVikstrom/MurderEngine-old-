#include <iostream>
#include <string>
#include "engine/MurderEngine.h"
#include "engine/scene/scene.h"
#include "engine/loaders/mesh_loader.h"
#include "engine/loaders/shader_loader.h"

int main()
{
  me::engine_init();
  me::engine_window("Murder Engine", 1550, 770, true, false);
  me::engine_setup_renderer_api("opengl");

  unsigned int vertexShader, fragmentShader;
  loader::loadShader("/home/edvinskomputa/Dokument/OnePunchEngine/src/res/shaders/me_vertex_shader.glsl", vertexShader, ME_SHADER_TYPE_VERTEX);
  loader::loadShader("/home/edvinskomputa/Dokument/OnePunchEngine/src/res/shaders/me_fragment_shader.glsl", fragmentShader, ME_SHADER_TYPE_FRAGMENT);
  unsigned int shader;
  loader::linkShaders(shader, new unsigned int[2]{vertexShader, fragmentShader}, 2);
  me::scene* scene = new me::scene("testar ju bara en scene", 0, 0, 1550, 770, true, shader);
  me::engine_register_event(scene);

  unsigned int itemCount;
  std::vector<me::item*> items = me::loadMeshFromFile("/home/edvinskomputa/Dokument/OnePunchEngine/src/res/test3.dae", itemCount);
  for (me::item* item : items)
  {
    if (item->type==ME_ITEM_TYPE_MESH)
      me::loadMesh(((me::mesh_item*)item)->mesh, -1); //TODO: STATIC_USE at param[1]
  }

  scene->setup();
  for (me::item* item : items)
    scene->registerItem(item);

  /* Starts the engine */
  me::engine_loop();
  return 0;
}
