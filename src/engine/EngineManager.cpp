#include <vector>

#include "EngineManager.h"
#include "utilities/Logger.h"

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
static std::vector<me::light*> lights;
static std::vector<me::camera*> cameras;
static std::vector<me::shader*> shaders;

static std::vector<me::sim::simulation*> simulations;

me::image* me::getImage(unsigned int id) { return images[id-1]; }
me::material* me::getMaterial(unsigned int id) { return materials[id-1]; }
me::mesh* me::getMesh(unsigned int id) { return meshes[id-1]; }
me::light* me::getLight(unsigned int id) { return lights[id-1]; }
me::camera* me::getCamera(unsigned int id) { return cameras[id-1]; }
me::shader* me::getShader(unsigned int id) { return shaders[id-1]; }

me::sim::simulation* getSimulation(unsigned int id) { return simulations[id-1]; }

unsigned int me::registerImage(me::image* image)
{
  images.push_back(image);
  return images.size();
}
unsigned int me::registerMaterial(me::material* material)
{
  materials.push_back(material);
  return materials.size();
}
unsigned int me::registerMesh(me::mesh* mesh)
{
  meshes.push_back(mesh);
  return meshes.size();
}
unsigned int me::registerLight(me::light* light)
{
  lights.push_back(light);
  return lights.size();
}
unsigned int me::registerCamera(me::camera* camera)
{
  cameras.push_back(camera);
  return cameras.size();
}
unsigned int me::registerShader(me::shader* shader)
{
  shaders.push_back(shader);
  return shaders.size();
}

unsigned int me::registerSimulation(me::sim::simulation* simulation)
{
  simulations.push_back(simulation);
  return simulations.size();
}

void me::cleanup()
{
  MANAGER_LOGGER->out("  % cleaning up\n");
  unsigned long mem = 0;
  MANAGER_LOGGER->out("  - \e[3m images\e[0m\n");
  for (me::image* image : images)
  {
    long use = image->mem_use();
    mem+=use;
    MANAGER_LOGGER->debug(std::string("  -- \e[3m image[") + image->identifier + "] | " + std::to_string(use) + "MiB\e[0m\n");
    delete image;
  }
  MANAGER_LOGGER->out("  - \e[3m materials\e[0m\n");
  for (me::material* material : materials)
  {
    long use = material->mem_use();
    mem+=use;
    MANAGER_LOGGER->debug(std::string("  -- \e[3m material[") + material->identifier + "] | " + std::to_string(use) + "MiB\e[0m\n");
    delete material;
  }
  MANAGER_LOGGER->out("  - \e[3m meshes\e[0m\n");
  for (me::mesh* mesh : meshes)
  {
    long use = mesh->mem_use();
    mem+=use;
    MANAGER_LOGGER->debug(std::string("  -- \e[3m image[") + mesh->identifier + "] | " + std::to_string(use) + "MiB\e[0m\n");
    delete mesh;
  }
  MANAGER_LOGGER->out("  - \e[3m lights\e[0m\n");
  for (me::light* light : lights)
  {
    long use = light->mem_use();
    mem+=use;
    MANAGER_LOGGER->debug(std::string("  -- \e[3m light[") + light->identifier + "] | " + std::to_string(use) + "MiB\e[0m\n");
    delete light;
  }
  MANAGER_LOGGER->out("  - \e[3m cameras\e[0m\n");
  for (me::camera* camera : cameras)
  {
    long use = camera->mem_use();
    mem+=use;
    MANAGER_LOGGER->debug(std::string("  -- \e[3m camera[") + camera->identifier + "] | " + std::to_string(use) + "MiB\e[0m\n");
    delete camera;
  }
  MANAGER_LOGGER->out("  - \e[3m shaders\e[0m\n");
  for (me::shader* shader : shaders)
  {
    long use = shader->mem_use();
    mem+=use;
    MANAGER_LOGGER->debug(std::string("  -- \e[3m shader[") + shader->identifier + "] | " + std::to_string(use) + "MiB\e[0m\n");
    delete shader;
  }
  MANAGER_LOGGER->out("  - \e[3m simulations\e[0m\n");
  for (me::sim::simulation* simulation : simulations)
  {
    long use = simulation->mem_use();
    mem+=use;
    MANAGER_LOGGER->debug(std::string("  -- \e[3m simulation[") + simulation->name + "] | " + std::to_string(use) + "MiB\e[0m\n");
    delete simulation;
  }
  images.clear();
  materials.clear();
  meshes.clear();
  lights.clear();
  cameras.clear();
  shaders.clear();
  simulations.clear();
  MANAGER_LOGGER->out(std::string("Cleaned up ") + std::to_string(((long double)mem / 1024.0L / 1024.0L)) + "MiB\n");
}
