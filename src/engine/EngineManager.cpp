#include <vector>

#include "EngineManager.h"

extern std::string RENDER_API;

namespace me {

  static std::vector<me::image*> images;
  static std::vector<me::material*> materials;
  static std::vector<me::mesh*> meshes;
  static std::vector<me::light*> lights;
  static std::vector<me::camera*> cameras;
  static std::vector<me::shader*> shaders;

  me::image* getImage(unsigned int id) { return images[id-1]; }
  me::material* getMaterial(unsigned int id) { return materials[id-1]; }
  me::mesh* getMesh(unsigned int id) { return meshes[id-1]; }
  me::light* getLight(unsigned int id) { return lights[id-1]; }
  me::camera* getCamera(unsigned int id) { return cameras[id-1]; }
  me::shader* getShader(unsigned int id) { return shaders[id-1]; }

  unsigned int registerImage(me::image* image)
  {
    images.push_back(image);
    return images.size();
  }
  unsigned int registerMaterial(me::material* material)
  {
    materials.push_back(material);
    return materials.size();
  }
  unsigned int registerMesh(me::mesh* mesh)
  {
    meshes.push_back(mesh);
    return meshes.size();
  }
  unsigned int registerLight(me::light* light)
  {
    lights.push_back(light);
    return lights.size();
  }
  unsigned int registerCamera(me::camera* camera)
  {
    cameras.push_back(camera);
    return cameras.size();
  }
  unsigned int registerShader(me::shader* shader)
  {
    shaders.push_back(shader);
    return shaders.size();
  }

};
