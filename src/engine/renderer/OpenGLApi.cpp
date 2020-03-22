#include <GL/glew.h>
#include <GL/glu.h>
#include "OpenGLApi.h"

// TODO: Fix error handling (return glGetError())

static const unsigned int ARGS[] {
  GL_TRIANGLES,
  GL_QUADS,
  GL_TRIANGLE_STRIP,
  GL_QUAD_STRIP,
  GL_POLYGON,
  GL_LINES,
  GL_LINE_STRIP,
  GL_LINE_LOOP,

  GL_TEXTURE_2D,
  GL_TEXTURE_3D,
  GL_NEAREST,
  GL_LINEAR,

  GL_PROJECTION,
  GL_MODELVIEW,

  GL_CULL_FACE,
  GL_BACK,
  GL_FRONT,
  GL_FRONT_AND_BACK,

  GL_DEPTH_TEST
};

OpenGLApi::OpenGLApi()
{

}

OpenGLApi::~OpenGLApi()
{

}

int OpenGLApi::initializeApi()
{
  glewInit();
  glClearColor(0.0F, 0.0F, 0.0F, 1.0F);
  return 1;
}

int OpenGLApi::enable(int a)
{
  glEnable(ARGS[a]);
  return 1;
}
int OpenGLApi::disable(int a)
{
  glDisable(ARGS[a]);
  return 1;
}

int OpenGLApi::createMeshIdentifier(me::mesh* mesh)
{
  // TODO:
  return 1;
}
int OpenGLApi::createImageIdentifier(me::image* image)
{
  // TODO:
  return 1;
}

/* Render Stuff */
int OpenGLApi::clear()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  return 1;
}
int OpenGLApi::shader(unsigned int shader)
{
  glUseProgram(shader);
  return 1;
}
int OpenGLApi::renderMesh(me::mesh* mesh)
{
  // TODO:

  glBindVertexArray(mesh->VAO);
  glDrawElements(GL_TRIANGLES, mesh->indices.size(), GL_UNSIGNED_INT, nullptr);
  glBindVertexArray(0);

  /*
  glBegin(GL_TRIANGLES);
  for (int i = 0; i < mesh->vertices.size(); i+=8)
  {
    glTexCoord2f(mesh->vertices[i+6], mesh->vertices[i+7]);
    glNormal3f(mesh->vertices[i+3], mesh->vertices[i+4], mesh->vertices[i+5]);
    glVertex3f(mesh->vertices[i], mesh->vertices[i+1], mesh->vertices[i+2]);
  }
  glEnd();
  */
  return 1;
}
int OpenGLApi::bind(int type, unsigned int bind)
{
  // TODO: ?
  if (type==ME_TEXTURE_2D)
  {
    glBindTexture(GL_TEXTURE_2D, bind);
    return 1;
  }
  return 0;
}

int OpenGLApi::renderBegin(int mode)
{
  glBegin(ARGS[mode]);
  return 1;
}
int OpenGLApi::renderEnd()
{
  glEnd();
  return 1;
}

int OpenGLApi::renderColor3f(float r, float g, float b)
{
  glColor3f(r, g, b);
  return 1;
}
int OpenGLApi::renderColor4f(float r, float g, float b, float a)
{
  glColor4f(r, g, b, a);
  return 1;
}
int OpenGLApi::renderColor3i(int r, int g, int b)
{
  glColor3i(r, g, b);
  return 1;
}
int OpenGLApi::renderColor4i(int r, int g, int b, int a)
{
  glColor4i(r, g, b, a);
  return 1;
}

int OpenGLApi::renderVertex2i(int x, int y)
{
  glVertex2i(x, y);
  return 1;
}
int OpenGLApi::renderVertex3i(int x, int y, int z)
{
  glVertex3i(x, y, z);
  return 1;
}
int OpenGLApi::renderVertex2f(float x, float y)
{
  glVertex2f(x, y);
  return 1;
}
int OpenGLApi::renderVertex3f(float x, float y, float z)
{
  glVertex3f(x, y, z);
  return 1;
}
int OpenGLApi::renderVertex2d(double x, double y)
{
  glVertex2d(x, y);
  return 1;
}
int OpenGLApi::renderVertex3d(double x, double y, double z)
{
  glVertex3d(x, y, z);
  return 1;
}
int OpenGLApi::light()
{
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);
  return 1;
}

/* Transformation */
int OpenGLApi::translatef(float x, float y, float z)
{
  glTranslatef(x, y, z);
  return 1;
}
int OpenGLApi::translated(double x, double y, double z)
{
  glTranslated(x, y, z);
  return 1;
}

int OpenGLApi::rotatef(float angle, float x, float y, float z)
{
  glRotatef(angle, x, y, z);
  return 1;
}
int OpenGLApi::rotated(double angle, double x, double y, double z)
{
  glRotated(angle, x, y, z);
  return 1;
}
int OpenGLApi::rotatef(float x, float y, float z)
{
  glRotatef(x, 1, 0, 0);
  glRotatef(y, 0, 1, 0);
  glRotatef(z, 0, 0, 1);
  return 1;
}
int OpenGLApi::rotated(double x, double y, double z)
{
  glRotated(x, 1, 0, 0);
  glRotated(y, 0, 1, 0);
  glRotated(z, 0, 0, 1);
  return 1;
}

int OpenGLApi::scalef(float x, float y, float z)
{
  glScalef(x, y, z);
  return 1;
}
int OpenGLApi::scaled(double x, double y, double z)
{
  glScaled(x, y, z);
  return 1;
}

/* Matrix */
int OpenGLApi::matrix(int matrix)
{
  glMatrixMode(ARGS[matrix]);
  return 1;
}

/* Viewport */
int OpenGLApi::viewport(int x, int y, unsigned int width, unsigned int height)
{
  glViewport(x, y, width, height);
  return 1;
}
int OpenGLApi::ortho(double left, double right, double bottom, double top, double znear, double zfar)
{
  glOrtho(left, right, bottom, top, znear, zfar);
  return 1;
}
int OpenGLApi::frustum(double left, double right, double bottom, double top, double znear, double zfar)
{
  glFrustum(left, right, bottom, top, znear, zfar);
  return 1;
}
int OpenGLApi::perspective(double fov, double aspect, double znear, double zfar)
{
  gluPerspective(fov, aspect, znear, zfar);
  return 1;
}

/* Other Stuff */
int OpenGLApi::loadIdentity()
{
  glLoadIdentity();
  return 1;
}
int OpenGLApi::pushMatrix()
{
  glPushMatrix();
  return 1;
}
int OpenGLApi::popMatrix()
{
  glPopMatrix();
  return 1;
}
int OpenGLApi::cullFace(int face)
{
  glCullFace(ARGS[face]);
  return 1;
}
int OpenGLApi::useAlpha(bool alpha)
{
  if (alpha)
  {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  }else
    glDisable(GL_BLEND);
  return 1;
}

int OpenGLApi::line(me::vec4f &color, me::vec3d &from, me::vec3d &to)
{
  glPushAttrib(GL_CURRENT_BIT);
  glColor4f(color.x, color.y, color.z, color.w);
  glBegin(GL_LINES);
  glVertex3d(from.x, from.y, from.z);
  glVertex3d(to.x, to.y, to.z);
  glEnd();
  glPopAttrib();
  return 1;
}
