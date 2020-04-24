#include "scene_2d_viewport.h"
#include "../../loader/scene_format.h"
#include "../../loader/image_format.h"
#include "../../loader/file_format.h"
#include "../../audio/audio_system.h"

#include <iostream> // remove

static void button_press()
{

}

void me::scene_2d_viewport::onPreInit(MeInstance* instance) { }
void me::scene_2d_viewport::onDestroyed(MeInstance* instance) { }

me::AudioTrack* track = nullptr;

void me::scene_2d_viewport::onInit(MeInstance* instance)
{
  float aspect = (float)width/(float)height;
  me::vec3 position(0, 0, 0);
  me::vec3 rotation(0.0F, 0.0F, 0.0F);
  scene::camera = new me::Camera("camera", me::CameraProjection::PROJ_PERSPECTIVE, me::maths::to_radians(70.0F), aspect, 0.1F, 100.0F, position, rotation);
  scene::onInit(instance);

  /* reading scene data */
  me::ScenePacket* packet = new me::ScenePacket;
  me::format::loadScene(instance, "/home/edvinskomputa/Dokument/OnePunchEngine/src/res/mega test of doom.dae", packet);

  track = new me::AudioTrack;
  track->waveform = new me::AudioWave;
  track->info.format = ME_AUD_FORMAT_S32BIT_PCM;
  track->info.sampleRate = 44100;
  track->info.channels = 2;
  //track->waveform->bytes = me::format::loadRAWData(instance, "ignoreme/CheatCxdes.raw", track->waveform->length);
  me::format::loadAudio(instance, "ignoreme/CheatCxdes.flac", track);

  uint32_t track_id = me::audio::register_track(track);
  me::audio::load_track(track_id);
  me::audio::play_track(track_id);

  /*
  uint32_t width = 1920 * 4;
  uint32_t height = 256;
  me::Bitmap* bitmap = new me::Bitmap {width, height, 24, new unsigned char[width * height * 3]};
  me::Image* bild = new me::Image(bitmap, {0, "", "", nullptr, ImageFormat::ME_IMG_FORMAT_RGB});
  me::ImageRasterizer rasterizer(bild);
  rasterizer.fill_rect(0x00000000, 0, 0, width, height);
  int x = 0;
  for (uint32_t i = 0; x < width; i+=1)
  {
    unsigned char y = track->waveform->bytes[44100 + i];
    rasterizer.fill_rect(0x0014FFFF, x, 0, 1, y);
    x++;
  }
  rasterizer.flip_vertical();
  me::format::writeImage(instance, "ignoreme/graph.bmp", me::format::ImageFileFormat::IFF_BMP, bild);
*/

  /* setting up renderer */
  instance->renderer->setupMeshRenderer(instance);
  instance->renderer->setupImageRenderer(instance);
}

void me::scene_2d_viewport::onRender(MeRenderer* renderer)
{
  scene::onRender(renderer);
}
void me::scene_2d_viewport::onLoop(MeInstance* instance)
{
  if (isPressed(instance, ME_KEY_W) || isPressed(instance, ME_KEY_A) || isPressed(instance, ME_KEY_S) || isPressed(instance, ME_KEY_D))
  {
    float speed = 0.5F;
    if (isPressed(instance, ME_KEY_W))
      scene::camera->move(0.0F, 0.0F, -speed);
    if (isPressed(instance, ME_KEY_A))
      scene::camera->move(-speed, 0.0F, 0.0F);
    if (isPressed(instance, ME_KEY_S))
      scene::camera->move(0.0F, 0.0F, speed);
    if (isPressed(instance, ME_KEY_D))
      scene::camera->move(speed, 0.0F, 0.0F);
    scene::camera->update_matrix();
  }
  scene::onLoop(instance);
}

bool me::scene_2d_viewport::onMouseInput(MeInstance* instance, int action, double posX, double posY, int button)
{
  if (action==ME_MOUSE_SCROLL)
  {
    scene::camera->move(0.0F, 0.0F, -((float)posY));
    scene::camera->update_matrix();
  }else if (action==ME_MOUSE_MOVE && isPressed(instance, ME_MOUSE_MIDDLE_BUTTON))
  {
    scene::camera->rotate(posX * 0.005F, posY * 0.005F, 0.0F);
    scene::camera->update_matrix();
  }
  return scene::onMouseInput(instance, action, posX, posY, button);
}
bool me::scene_2d_viewport::onKeyInput(MeInstance* instance, int action, int key)
{
  if (action == ME_PRESS)
  {
    if (key == ME_KEY_SPACE)
      track->state.playing = !track->state.playing;
    else if (key == ME_KEY_UP)
      track->state.gain+=0.1F;
    else if (key == ME_KEY_DOWN)
      track->state.gain-=0.1F;
  }
  return scene::onKeyInput(instance, action, key);
}
