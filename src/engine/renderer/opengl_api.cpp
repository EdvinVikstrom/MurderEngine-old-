#include "../scene/scene.h"
#include "../utilities/Logger.h"
#include "../MurderEngine.h"
#include "../EngineManager.h"
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
  glDrawElements(GL_TRIANGLES, mesh->indices->count, GL_UNSIGNED_INT, nullptr);
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
int opengl_api::material(me::material* material)
{
  return ME_FINE;
}

int opengl_api::reset()
{
  glLoadIdentity();
  return ME_FINE;
}
int opengl_api::transform(me::transform &transform)
{
  glUniform3f(0, transform.location.x, transform.location.y, transform.location.z);
  glUniform3f(1, transform.rotation.x, transform.rotation.y, transform.rotation.z);
  glUniform3f(2, transform.scale.x, transform.scale.y, transform.scale.z);
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
