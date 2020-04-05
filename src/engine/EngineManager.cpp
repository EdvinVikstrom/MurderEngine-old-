#include <vector>
#include <map>
#include "EngineManager.h"
#include "kernel/kernel.h"
#include "utilities/Logger.h"

#include "loaders/image_reader.h"
#include "loaders/mesh_reader.h"

extern std::string RENDER_API;

static me::log* MANAGER_LOGGER = new me::log("EngineManager",
"\e[32m[%N] %T #%M \e[0m",
"\e[32m[%N] %T\e[0m \e[33m#%M \e[0m",
"\e[32m[%N] %T\e[0m \e[31m#%M \e[0m",
"\e[34m[%N] %T #%M \e[0m"
);

static std::vector<me::image*> images;
static std::vector<me::material*> materials;
static std::vector<me::mesh*> meshes;
static std::vector<me::camera*> cameras;
static std::vector<me::light*> lights;

static std::map<std::string, uint32_t> imageLinks;
static std::map<std::string, uint32_t> materialLinks;
static std::map<std::string, uint32_t> meshLinks;
static std::map<std::string, uint32_t> cameraLinks;
static std::map<std::string, uint32_t> lightLinks;

me::image* me::getImage(unsigned int id) { return images[id-1]; }
me::material* me::getMaterial(unsigned int id) { return materials[id-1]; }
me::mesh* me::getMesh(unsigned int id) { return meshes[id-1]; }
me::camera* me::getCamera(unsigned int id) { return cameras[id-1]; }
me::light* me::getLight(unsigned int id) { return lights[id-1]; }

unsigned int me::getImageLink(std::string identifier) { return imageLinks[identifier.c_str()]; }
unsigned int me::getMaterialLink(std::string identifier) { return materialLinks[identifier.c_str()]; }
unsigned int me::getMeshLink(std::string identifier) { return meshLinks[identifier.c_str()]; }
unsigned int me::getCameraLink(std::string identifier) { return cameraLinks[identifier.c_str()]; }
unsigned int me::getLightLink(std::string identifier) { return lightLinks[identifier.c_str()]; }

unsigned int me::registerImage(me::image* image)
{
  image->imageId = me::fformat::load_image(image);
  images.push_back(image);
  imageLinks[image->identifier.c_str()] = images.size();
  return images.size();
}
unsigned int me::registerMaterial(me::material* material)
{
  materials.push_back(material);
  materialLinks[material->identifier.c_str()] = materials.size();
  return materials.size();
}
unsigned int me::registerMesh(me::mesh* mesh)
{
  me::fformat::load_mesh(mesh, -1); // TODO: useage
  meshes.push_back(mesh);
  meshLinks[mesh->identifier.c_str()] = meshes.size();
  return meshes.size();
}
unsigned int me::registerCamera(me::camera* camera)
{
  cameras.push_back(camera);
  cameraLinks[camera->identifier.c_str()] = cameras.size();
  return cameras.size();
}
unsigned int me::registerLight(me::light* light)
{
  lights.push_back(light);
  lightLinks[light->identifier.c_str()] = lights.size();
  return lights.size();
}

void me::init()
{
  me::fformat::init();
}

void me::cleanup()
{
  MANAGER_LOGGER->out("  % cleaning up\n");

  me::fformat::cleanup();

  MANAGER_LOGGER->out("  - \e[3m images\e[0m\n");
  for (me::image* image : images)
  {
    delete image;
  }
  MANAGER_LOGGER->out("  - \e[3m materials\e[0m\n");
  for (me::material* material : materials)
  {
    delete material;
  }
  MANAGER_LOGGER->out("  - \e[3m meshes\e[0m\n");
  for (me::mesh* mesh : meshes)
  {
    delete mesh;
  }
  MANAGER_LOGGER->out("  - \e[3m cameras\e[0m\n");
  for (me::camera* camera : cameras)
  {
    delete camera;
  }
  MANAGER_LOGGER->out("  - \e[3m lights\e[0m\n");
  for (me::light* light : lights)
  {
    delete light;
  }
  images.clear();
  materials.clear();
  meshes.clear();
  cameras.clear();
  lights.clear();
  MANAGER_LOGGER->out("Cleaned up\n");
}
