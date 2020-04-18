#include "opengl_api.h"

#include "../../kernel/log.h"
#include "../../loader/image_format.h"

#include <GL/glew.h>

static int getUniformLocation(int program, std::string varName)
{
  return glGetUniformLocation(program, varName.c_str());
}

static int getPolygonMode(me::Polygon mode)
{
  if (mode==me::Polygon::POINT)
    return GL_POINTS;
  else if (mode==me::Polygon::LINE)
    return GL_LINES;
  else if (mode==me::Polygon::TRIANGLE)
    return GL_TRIANGLES;
  else if (mode==me::Polygon::QUAD)
    return GL_QUADS;
  return -1;
}

int me::opengl_api::initializeApi(MeInstance* instance)
{
  glewInit();
  program = instance->renderer->info->shaderProgram;
  int shaders[program->shaders.size()];
  uint32_t i = 0;
  for (auto const &[key, value] : program->shaders)
  {
    int type = 0;
    if (key==MeShaderType::VERTEX) type = GL_VERTEX_SHADER;
    else if (key==MeShaderType::TESSELLATION) type =  GL_TESS_CONTROL_SHADER;
    else if (key==MeShaderType::GEOMETRY) type =  GL_GEOMETRY_SHADER;
    else if (key==MeShaderType::FRAGMENT) type = GL_FRAGMENT_SHADER;
    shaders[i] = glCreateShader(type);
    const char* str =  value.c_str();
    glShaderSource(shaders[i], 1, &str, nullptr);
    glCompileShader(shaders[i]);
    int compiled;
    glGetShaderiv(shaders[i], GL_COMPILE_STATUS, &compiled);
    if (compiled != GL_TRUE)
    {
      int log_length = 0;
      char log[1024];
      glGetShaderInfoLog(shaders[i], 1024, &log_length, log);
      std::cout << LOG_COLOR_RED << "[OpenGL] [ERR]: Failed to compile shader | " << log << "\n" << LOG_ANSI_RESET;
      return ME_ERR;
    }
    i++;
  }
  unsigned int program_id = glCreateProgram();
  for (uint32_t i = 0; i < program->shaders.size(); i++)
    glAttachShader(program_id, shaders[i]);
  glLinkProgram(program_id);
  glValidateProgram(program_id);
  int linked;
  glGetProgramiv(program_id, GL_LINK_STATUS, &linked);
  if (linked != GL_TRUE)
  {
    int log_length = 0;
    char log[1024];
    glGetShaderInfoLog(shaders[i], 1024, &log_length, log);
    std::cout << LOG_COLOR_RED << "[OpenGL] [ERR]: Failed to link shaders | " << log << "\n" << LOG_ANSI_RESET;
  }
  glUseProgram(program_id);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);

  instance->loadStandardModels();
  return ME_FINE;
}

int me::opengl_api::setupMeshRenderer(MeInstance* instance)
{
  for (me::Mesh* mesh : instance->meshes)
    loadMesh(mesh);
  return ME_FINE;
}
int me::opengl_api::setupImageRenderer(MeInstance* instance)
{
  for (me::Image* image : instance->images)
    loadImage(image);
  return ME_FINE;
}
int me::opengl_api::loadMesh(me::Mesh* mesh)
{
  bool has_color = mesh->colors.size() != 0;
  glGenVertexArrays(1, &mesh->buffer);
  unsigned int positionVBO;
  unsigned int normalVBO;
  unsigned int texCoordVBO;
  unsigned int colorVBO;
  unsigned int index_buffer;
  glGenBuffers(1, &positionVBO);
  glGenBuffers(1, &normalVBO);
  glGenBuffers(1, &texCoordVBO);
  if (has_color) glGenBuffers(1, &colorVBO);

  glGenBuffers(1, &index_buffer);
  glBindVertexArray(mesh->buffer);

  glBindBuffer(GL_ARRAY_BUFFER, positionVBO);
  glBufferData(GL_ARRAY_BUFFER, mesh->vertices.size() * sizeof(me::vertex), &mesh->vertices[0], GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->indices.size() * sizeof(uint32_t), &mesh->indices[0], GL_STATIC_DRAW);

  unsigned int stride = sizeof(me::vertex);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, false, stride, (void*)0);

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, false, stride, (void*)12);

  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, false, stride, (void*)24);

  glEnableVertexAttribArray(3);
  glVertexAttribPointer(3, 4, GL_FLOAT, false, stride, (void*)32);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(2);
  if (has_color) glDisableVertexAttribArray(3);
  glBindVertexArray(0);
  return ME_FINE;
}
int me::opengl_api::loadImage(me::Image* image)
{
  glEnable(GL_TEXTURE_2D);
  glGenTextures(1, &image->info.glBindId);
  glBindTexture(GL_TEXTURE_2D, image->info.glBindId);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  int internal_format = 0;
  int external_format = 0;
  if (image->info.format == ME_IMG_FORMAT_RGB)
  {
    internal_format = GL_RGB8;
    external_format = GL_RGB;
  }else if (image->info.format == ME_IMG_FORMAT_RGBA)
  {
    internal_format = GL_RGBA8;
    external_format = GL_RGBA;
  }
  glTexImage2D(GL_TEXTURE_2D, 0, internal_format, image->bitmap->width, image->bitmap->height, 0, external_format, GL_UNSIGNED_BYTE, image->bitmap->map);
  glBindTexture(GL_TEXTURE_2D, 0);
  glDisable(GL_TEXTURE_2D);
  return ME_FINE;
}

int me::opengl_api::uniformMatrix4(int location, me::maths::mat4 matrix)
{
  glUniformMatrix4fv(location, 1, GL_FALSE, matrix.array);
  return ME_FINE;
}
int me::opengl_api::uniformVec2(int location, me::vec2 vec)
{
  return ME_FINE;
}
int me::opengl_api::uniformVec3(int location, me::vec3 vec)
{
  glUniform3f(location, vec.x, vec.y, vec.z);
  return ME_FINE;
}
int me::opengl_api::uniformVec4(int location, me::vec4 vec)
{
  glUniform4f(location, vec.x, vec.y, vec.z, vec.w);
  return ME_FINE;
}

static void bindTextureSampler(uint32_t imageId, int sampler)
{
  glActiveTexture(GL_TEXTURE0 + sampler);
  glBindTexture(GL_TEXTURE_2D, imageId);
}

static void bindWColor(me::wcolor* color, int location, int slot)
{
  if (color == nullptr)
  {
    glUniform1i(location, -1);
    return;
  }
  if (color->type==0)
  {
    glUniform1i(location, 0);
    bindTextureSampler(((me::Image*)color->data)->info.glBindId, slot);
    glUniform1i(location + 1, slot);
  }
  else if (color->type==1)
  {
    me::vec4* vec = (me::vec4*) color->data;
    glUniform1i(location, 1);
    glUniform4f(location + 2, vec->x, vec->y, vec->z, vec->w);
  }else if (color->type==2)
  {
    glUniform1i(location, 1);
    glUniform1f(location + 2, *((float*)color->data));
  }
}
static void bindMaterial(me::Material* material)
{
  me::wcolor* diffuse = material->diffuse;
  me::wcolor* specular = material->specular;
  me::wcolor* emission = material->specular;
  me::wcolor* gloss = material->specular;
  me::wcolor* ior = material->specular;
  glEnable(GL_TEXTURE_2D);

  bindWColor(diffuse, 3, 0);
  bindWColor(specular, 6, 0);
  //bindWColor(emission, 9, 0);
  //bindWColor(gloss, 12, 0);
  //bindWColor(ior, 15, 0);

  glDisable(GL_TEXTURE_2D);
}

static void renderMesh(me::Mesh* mesh, me::Material* material, me::Polygon mode)
{
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);
  glEnableVertexAttribArray(3);

  if (material != nullptr)
    bindMaterial(material);
  glDrawElements(getPolygonMode(mode), mesh->indices.size(), GL_UNSIGNED_INT, nullptr);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(2);
  glDisableVertexAttribArray(3);
}

int me::opengl_api::renderFrame(MeInstance* instance, unsigned long current_frame, bool &framebuffer_resized)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  uint32_t index = 0;
  for (me::Light* light : instance->lights)
  {
    float x = light->model_matrix.x();
    float y = light->model_matrix.y();
    float z = light->model_matrix.z();

    glPointSize(15.0F);

    /* bind light */
    glUniform3f(18+index, x, y, z);
    glUniform3f(19+index, light->rgba.x, light->rgba.y, light->rgba.z);

    /* model matrix */
    glUniformMatrix4fv(2, 1, GL_FALSE, light->model_matrix.array);

    /* diffuse color */
    glUniform1i(3, 1);
    glUniform4f(3 + 2,
      light->rgba.x / light->power,
      light->rgba.y / light->power,
      light->rgba.z / light->power, 1.0F);

    /* bind and draw mesh */
    glBindVertexArray(instance->lightMesh->buffer);
    renderMesh(instance->lightMesh, nullptr, me::Polygon::POINT);
    glBindVertexArray(0);

    index+=2;
  }
  for (uint32_t i = index; i < MeShaderProgram::MAX_LIGHTS * 2; i+=2)
  {
    glUniform3f(18+i, 0.0F, 0.0F, 0.0F);
    glUniform3f(19+i, -1.0F, -1.0F, -1.0F);
  }
  for (me::Mesh* mesh : instance->meshes)
  {
    me::Material* material = mesh->materials.at(0);
    glUniformMatrix4fv(2, 1, GL_FALSE, mesh->model_matrix.array);

    glBindVertexArray(mesh->buffer);
    renderMesh(mesh, material, mesh->mode);
    glBindVertexArray(0);
  }
  return ME_FINE;
}
int me::opengl_api::cleanup()
{
  return ME_FINE;
}
