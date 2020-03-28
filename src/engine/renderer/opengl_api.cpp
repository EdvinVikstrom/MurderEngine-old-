#include "../scene/scene.h"
#include "../utilities/Logger.h"
#include "../MurderEngine.h"
#include "../EngineManager.h"
#include "opengl_api.h"
#include <GL/glew.h>
#include <GL/glu.h>

me::log* OPENGL_LOGGER = new me::log("OpenGL", "\e[36m[%N] %T #%M \e[0m");

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
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  return ME_FINE;
}
int opengl_api::viewport(me::camera* camera, int x, int y, unsigned int width, unsigned int height)
{
  glMatrixMode(GL_PROJECTION);
  glViewport(x, y, width, height);
  if (camera->type==ME_CAMERA_PERSPECTIVE)
  {
    gluPerspective(camera->focalLength, camera->aspectRatio, camera->znear, camera->zfar);
    glEnable(GL_DEPTH_TEST);
  }
  else if (camera->type==ME_CAMERA_2D_VIEW)
  {
    glOrtho(0, width, height, 0, camera->znear, camera->zfar);
    glDisable(GL_DEPTH_TEST);
  }
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
  glPushMatrix();
  glPushAttrib(GL_CURRENT_BIT);
  return ME_FINE;
}
int opengl_api::pop()
{
  glPopMatrix();
  glPopAttrib();
  return ME_FINE;
}
int opengl_api::clear()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  return ME_FINE;
}
int opengl_api::vertex(float x, float y, float z)
{
  glVertex3f(x, y, z);
  return ME_FINE;
}
int opengl_api::renderStart(unsigned int type)
{
  glBegin(getParam(type));
  return ME_FINE;
}
int opengl_api::renderEnd()
{
  glEnd();
  return ME_FINE;
}

/*
me::material* material = me::getMaterial(mesh->material);
glEnable(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE_2D, material->rgba->image->imageId);
glBegin(GL_TRIANGLES);
for (unsigned int i = 0; i < mesh->indices.count; i+=3)
{
  glTexCoord2f(mesh->vertices.values[mesh->indices.values[i+2]], mesh->vertices.values[mesh->indices.values[i+2]+1]);
  glNormal3f(mesh->vertices.values[mesh->indices.values[i+1]], mesh->vertices.values[mesh->indices.values[i+1]+1], mesh->vertices.values[mesh->indices.values[i+1]+2]);
  glVertex3f(mesh->vertices.values[mesh->indices.values[i]], mesh->vertices.values[mesh->indices.values[i]+1], mesh->vertices.values[mesh->indices.values[i]+2]);
}
glEnd();
glDisable(GL_TEXTURE_2D);
*/

int opengl_api::bindMesh(me::mesh* mesh)
{
  glBindVertexArray(mesh->VAO);
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);
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
int opengl_api::mesh(me::mesh* mesh)
{
 glDrawElements(GL_TRIANGLES, mesh->indices.count, GL_UNSIGNED_INT, nullptr);
  return ME_FINE;
}
int opengl_api::bindImage(me::image* image)
{
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, image->imageId);
  return ME_FINE;
}
int opengl_api::unbindImage()
{
  glBindTexture(GL_TEXTURE_2D, 0);
  glDisable(GL_TEXTURE_2D);
  return ME_FINE;
}
int opengl_api::plane(double posX, double posY, double scaleX, double scaleY)
{
  glBegin(GL_TRIANGLES);
  glVertex2d(posX, posY);
  glVertex2d(posX+scaleX, posY);
  glVertex2d(posX, posY+scaleY);

  glVertex2d(posX+scaleX, posY);
  glVertex2d(posX+scaleX, posY+scaleY);
  glVertex2d(posX, posY+scaleY);
  glEnd();
  return ME_FINE;
}
int opengl_api::color(float red, float green, float blue, float alpha)
{
  //glColor4f(red, green, blue, alpha);
  return ME_FINE;
}

int opengl_api::reset()
{
  glLoadIdentity();
  return ME_FINE;
}
int opengl_api::translate(double x, double y, double z, double w)
{
  glTranslated(x, y, z);
  return ME_FINE;
}
int opengl_api::rotate(double x, double y, double z, double w)
{
  glRotated(x, 1, 0, 0);
  glRotated(y, 0, 1, 0);
  glRotated(z, 0, 0, 1);
  return ME_FINE;
}
int opengl_api::scale(double x, double y, double z, double w)
{
  glScaled(x, y, z);
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
