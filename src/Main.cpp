#include <iostream>
#include <string>
#include "engine/MurderEngine.h"
#include "engine/EngineManager.h"
#include "engine/scene/scene.h"
#include "engine/scene/scenes/scene_2d_viewport.h"
#include "engine/scene/scenes/scene_outliner.h"
#include "engine/loaders/mesh_loader.h"

#include "engine/simulation/rigidbody/rigidbody.h"

int main()
{
  if (me::engine_init() != ME_FINE) return 1;
  if (me::engine_window("Murder Engine", 1550, 770, true, false) != ME_FINE) return 1;
  if (me::engine_setup_renderer_api("opengl") != ME_FINE) return 1;
  if (me::engine_load_shaders("src/res/shaders/shader.glsl") != ME_FINE) return 1;
/*
  unsigned int vertexShader, fragmentShader;
  loader::loadShader("/home/edvinskomputa/Dokument/OnePunchEngine/src/res/shaders/me_vertex_shader.glsl", vertexShader, ME_SHADER_TYPE_VERTEX);
  loader::loadShader("/home/edvinskomputa/Dokument/OnePunchEngine/src/res/shaders/me_fragment_shader.glsl", fragmentShader, ME_SHADER_TYPE_FRAGMENT);
  unsigned int shader;
  loader::linkShaders(shader, new unsigned int[2]{vertexShader, fragmentShader}, 2);
  */
  me::scene_outliner* scene1 = new me::scene_outliner("en outliner", 0, 0, 350, 770);
  me::scene_2d_viewport* scene2 = new me::scene_2d_viewport("en viewport", 0, 0, 1550, 770);
  //me::engine_register_event(scene1);
  me::engine_register_event(scene2);

  unsigned int itemCount;
  std::vector<me::item*> items = me::loadMeshFromFile("src/res/rubrub.dae", itemCount);
  for (me::item* item : items)
  {
    if (item->type==ME_ITEM_TYPE_MESH)
    {
      me::loadMesh(me::getMesh(((me::mesh_item*)item)->mesh), -1); // TODO: STATIC_USE at param[1]
      me::simulation* simulation = new me::rigidbody_simulation(ME_SIMULATION_MODE_ACTIVE, 0.2D, true, 1.0F, 0.0F);
      simulation->applyForce({0, -0.1D, 0}, 0.5F);
      item->simulations.push_back(simulation);
    }
  }

  //scene1->setup();
  scene2->setup();
  for (me::item* item : items)
    scene2->registerItem(item);

  /* Starts the engine */
  me::engine_loop();
  return 0;
}
