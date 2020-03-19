#include <GL/glew.h>
#include "OpenGLApi"

// TODO: Fix error handling (return glGetError())

static const unsigned int ARGS[] {
  GL_TRIANGLES,
  GL_QUADS,
  GL_TRIANGLE_STRIP,
  GL_QUAD_STRIP,
  GL_POLYGONS,

  GL_TEXTURE_2D,
  GL_TEXTURE_3D,
  GL_NEAREST,
  GL_LINEAR,

  GL_PROJECTION,
  GL_MODELVIEW,

  GL_CULL_FACE,
  GL_BACK,
  GL_FRONT
};

int OpenGLApi::initializeApi() override
{
  return glewInit();
}

int enable(int a) override
{
  glEnable(ARGS[a]);
  return 1;
}
int disable(int a) override
{
  glDisable(ARGS[a]);
  return 1;
}

int OpenGLApi::createMeshIdentifier(me::mesh* mesh) override
{
  // TODO:
  return 1;
}
int OpenGLApi::createImageIdentifier(me::image* image) override
{
  // TODO:
  return 1;
}

/* Render Stuff */
int clear() override
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  return 1;
}
int OpenGLApi::renderMesh(me::mesh* mesh) override
{
  // TODO:
  return 1;
}
int OpenGLApi::bind(int type, unsigned int bind) override
{
  // TODO: ?
  if (type==ME_RENDERER_TEXTURE_2D)
  {
    glBindTexture(GL_TEXTURE_2D, bind);
    return 1;
  }
  return 0;
}

int OpenGLApi::renderBegin(int mode) override
{
  glBegin(ARGS[mode]);
  return 1;
}
int OpenGLApi::renderEnd() override
{
  glEnd();
  return 1;
}

int OpenGLApi::renderColor3f(float r, float g, float b) override
{
  glColor3f(r, g, b);
  return 1;
}
int OpenGLApi::renderColor4f(float r, float g, float b, float a) override
{
  glColor4f(r, g, b, a);
  return 1;
}
int OpenGLApi::renderColor3i(int r, int g, int b) override
{
  glColor3i(r, g, b);
  return 1;
}
int OpenGLApi::renderColor4i(int r, int g, int b, int a) override
{
  glColor4i(r, g, b, a);
  return 1;
}

int OpenGLApi::renderVertex2i(int x, int y) override
{
  glVertex2i(x, y);
  return 1;
}
int OpenGLApi::renderVertex3i(int x, int y, int z) override
{
  glVertex3i(x, y, z);
  return 1;
}
int OpenGLApi::renderVertex2f(float x, float y) override
{
  glVertex2f(x, y);
  return 1;
}
int OpenGLApi::renderVertex3f(float x, float y, float z) override
{
  glVertex3f(x, y, z);
  return 1;
}
int OpenGLApi::renderVertex2d(double x, double y) override
{
  glVertex2d(x, y);
  return 1;
}
int OpenGLApi::renderVertex3d(double x, double y, double z) override
{
  glVertex3d(x, y, z);
  return 1;
}

/* Transformation */
int OpenGLApi::translatef(float x, float y, float z) override
{
  glTranslatef(x, y, z);
  return 1;
}
int OpenGLApi::translated(double x, double y, double z) override
{
  glTranslated(x, y, z);
  return 1;
}

int OpenGLApi::rotatef(float angle, float x, float y, float z) override
{
  glRotatef(angle, x, y, z);
  return 1;
}
int OpenGLApi::rotated(double angle, double x, double y, double z) override
{
  glRotated(angle, x, y, z);
  return 1;
}
int rotatef(float x, float y, float z) override
{
  glRotatef(x, 1, 0, 0);
  glRotatef(y, 0, 1, 0);
  glRotatef(z, 0, 0, 1);
  return 1;
}
int rotated(double x, double y, double z) override
{
  glRotated(x, 1, 0, 0);
  glRotated(y, 0, 1, 0);
  glRotated(z, 0, 0, 1);
  return 1;
}

int scalef(float x, float y, float z) override
{
  glScalef(x, y, z);
  return 1;
}
int scaled(double x, double y, double z) override
{
  glScaled(x, y, z);
  return 1;
}

/* Matrix */
int matrix(int matrix) override
{
  glMatrixMode(matrix);
}

/* Viewport */
int OpenGLApi::viewport(int x, int y, unsigned int width, unsigned int height) override
{
  glViewport(x, y, width, height);
  return 1;
}
int OpenGLApi::ortho(double left, double right, double bottom, double top, double znear, double zfar) override
{
  glOrtho(left, right, bottom, top, znear, zfar);
  return 1;
}
int frustum(double left, double right, double bottom, double top, double znear, double zfar) override
{
  glFrustum(left, right, bottom, top, znear, zfar);
  return 1;
}
int OpenGLApi::perspective(double left, double right, double bottom, double top, double znear, double zfar) override
{
  return 1;
}

/* Other Stuff */
int loadIdentity() override
{
  glLoadIdentity();
  return 1;
}
int cullFace(int face) override
{
  glCullFace(face);
  return 1;
}
