#include "../scene/scene.h"
#include "../utilities/Logger.h"
#include "../MurderEngine.h"
#include "../EngineManager.h"
#include "../math/matrix.h"
#include "opengl_api.h"
#include <GL/glew.h>
#include <GL/glu.h>
#include "../kernel/kernel.h"


#include "../math/maths.h" // remove

static me::log* OPENGL_LOGGER = new me::log("EngineManager",
"\e[36m[%N] %T #%M \e[0m",
"\e[36m[%N] %T\e[0m \e[33m#%M \e[0m",
"\e[36m[%N] %T\e[0m \e[31m#%M \e[0m",
"\e[34m[%N] %T #%M \e[0m"
);

unsigned int getParam(unsigned int i)
{
  unsigned int out = 0;
  switch (i) {
    case ME_TRIANGLES: out = GL_TRIANGLES; break;
    case ME_QUADS: out = GL_QUADS; break;
    case ME_TRIANGLE_STRIP: out = GL_TRIANGLE_STRIP; break;
    case ME_QUAD_STRIP: out = GL_QUAD_STRIP; break;
    case ME_POLYGONS: out = GL_POLYGON; break;
    case ME_LINES: out = GL_LINES; break;
    case ME_LINE_STRIP: out = GL_LINE_STRIP; break;
    case ME_LINE_LOOP: out = GL_LINE_LOOP; break;
    case ME_POINTS: out = GL_POINTS; break;
    default:
      OPENGL_LOGGER->err(std::string("Undefined type [") + std::to_string(i) + "]\n");
    break;
  }
  return out;
}

int opengl_api::initializeApi()
{
  if (glewInit() != GLEW_OK)
  {
    OPENGL_LOGGER->err("Failed to Initialize GLEW\n");
    return ME_ERR;
  }
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  return ME_FINE;
}
int opengl_api::viewport(me::camera* camera, int x, int y, unsigned int width, unsigned int height)
{
  glViewport(x, y, width, height);
  glMatrixMode(GL_PROJECTION);
  if (camera->type==me::camera_type::PERSPECTIVE)
    gluPerspective(camera->focalLength, camera->aspectRatio, camera->znear, camera->zfar);
  else if (camera->type==me::camera_type::ORTHOGRAPHIC)
    glOrtho(0, width, height, 0, camera->znear, camera->zfar);
  else if (camera->type==me::camera_type::VIEW_2D)
    glOrtho(0, width, height, 0, camera->znear, camera->zfar);
  else if (camera->type==me::camera_type::ENC_VIEW_2D)
    glFrustum(0, width, height, 0, camera->znear, camera->zfar);
  glMatrixMode(GL_MODELVIEW);
  return ME_FINE;
}
int opengl_api::useProgram(unsigned int program)
{
  glUseProgram(program);
  return ME_FINE;
}

int opengl_api::push()
{
  return ME_FINE;
}
int opengl_api::pop()
{
  return ME_FINE;
}
int opengl_api::clear()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  return ME_FINE;
}

int opengl_api::bindMesh(me::mesh* mesh)
{
  glBindVertexArray(mesh->VAO);
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);
  return ME_FINE;
}
int opengl_api::mesh(me::mesh* mesh)
{
  bindMaterial(mesh->indices.at(0)->material);
  glDrawElements(GL_TRIANGLES, mesh->indices.at(0)->indices.size(), GL_UNSIGNED_INT, nullptr);
  unbindMaterial();
  return ME_FINE;
}
int opengl_api::unbindMesh()
{
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(2);
  glBindVertexArray(0);
  return ME_FINE;
}
int opengl_api::bindMaterial(me::material* material)
{
  if (material->rgba != nullptr)
    bindTexture(material->rgba);
  return ME_FINE;
}
int opengl_api::unbindMaterial()
{
  unbindTexture();
  return ME_FINE;
}
int opengl_api::bindTexture(me::wcolor* texture)
{
  if (texture->type==me::wcolor_type::IMAGE)
  {
    glEnable(GL_TEXTURE_2D);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture->v_image->imageId);
    glUniform1i(3, 0);
  }else if (texture->type==me::wcolor_type::RGBA)
    glColor4f(texture->v_rgba->x, texture->v_rgba->y, texture->v_rgba->z, texture->v_rgba->w);
  return ME_FINE;
}
int opengl_api::unbindTexture()
{
  glDisable(GL_TEXTURE_2D);
  return ME_FINE;
}

int opengl_api::reset()
{
  glLoadIdentity();
  return ME_FINE;
}
int opengl_api::vec3f(int location, float x, float y, float z)
{
  glUniform3f(location, x, y, z);
  return ME_FINE;
}
int opengl_api::matrix4(int location, float* matrix)
{
  glUniformMatrix4fv(location, 1, GL_FALSE, matrix);
  return ME_FINE;
}
int opengl_api::modify(unsigned int p, float value)
{
  if (p==ME_POINTS)
  {
    glPointSize(value);
    return ME_FINE;
  }else if (p==ME_LINES)
  {
    glLineWidth(value);
    return ME_FINE;
  }
  return ME_ERR;
}

int opengl_api::terminate()
{
  return ME_FINE;
}
