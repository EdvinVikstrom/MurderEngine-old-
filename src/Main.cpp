#include <iostream>
#include <string>
#include "engine/MurderEngine.h"
#include "engine/scene/scene.h"
#include "engine/loaders/mesh_loader.h"

int main()
{
  me::engine_init();
  me::engine_window("Murder Engine", 1550, 770, true, false);
  me::engine_setup_renderer_api("opengl");

  me::scene* scene = new me::scene("testar ju bara en scene", 0, 0, 1550, 770, true);
  me::engine_register_scene(scene);

  unsigned int itemCount;
  std::vector<me::item*> items = me::loadMeshFromFile("/home/edvinskomputa/Dokument/OnePunchEngine/src/res/test3.dae", itemCount);
  //me::loadMesh(mesh, ME_MESH_USAGE_STATIC);
  //me::item* item = new me::mesh_item("ett fint item", new me::vec3d(0, 0, -4), new me::vec3d(0, 0, 0), new me::vec3d(0, 0, 0), mesh);
  scene->setup();
  for (me::item* item : items)
    scene->registerItem(item);

  /* Starts the engine */
  me::engine_loop();
  return 0;
}
