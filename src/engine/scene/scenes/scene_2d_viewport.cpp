#include "scene_2d_viewport.h"
#include "../../renderer/renderer_api.h"

extern renderer_api* rendererApi;

void me::scene_2d_viewport::setup()
{
  float aspect = (float)width/(float)height;
  scene::camera = new me::camera("camera", {0, 0, 0}, {0, 0, 0}, ME_CAMERA_PERSPECTIVE, aspect, 50, 0.1, 1000);
    rendererApi->viewport(me::scene::camera, x, y, width, height);
  particle_group* group = new particle_group({4, 0, 0}, {0, 0, 0}, 4, 0, false);
  group->meshes.push_back(1);
  for (unsigned int i = 0; i < 100; i++)
    group->particles.push_back(new particle(0, maths::rand(), 0, 65000));
  //scene::registerParticleGroup(group);
}

void me::scene_2d_viewport::onRender()
{
  scene::onRender();
}
void me::scene_2d_viewport::onLoop()
{
  scene::onLoop();

}

void me::scene_2d_viewport::onMouseInput(int action, double posX, double posY, int button)
{
  scene::onMouseInput(action, posX, posY, button);
}
void me::scene_2d_viewport::onKeyInput(int action, int key)
{
  scene::onKeyInput(action, key);
}
