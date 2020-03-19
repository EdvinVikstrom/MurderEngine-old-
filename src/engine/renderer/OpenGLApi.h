#ifndef OPENGL_API
  #define OPENGL_API

#include "RendererApi.h"

class OpenGLApi : public IRendererApi {

public:

  OpenGLApi();
  ~OpenGLApi();

  int initializeApi();

  int enable(int a);
  int disable(int a);

  int createMeshIdentifier(me::mesh* mesh);
  int createImageIdentifier(me::image* image);

  /* Render Stuff */
  int clear();

  int renderMesh(me::mesh* mesh);
  int bind(int type, unsigned int bind);

  int renderBegin(int mode);
  int renderEnd();

  int renderColor3f(float r, float g, float b);
  int renderColor4f(float r, float g, float b, float a);
  int renderColor3i(int r, int g, int b);
  int renderColor4i(int r, int g, int b, int a);

  int renderVertex2i(int x, int y);
  int renderVertex3i(int x, int y, int z);
  int renderVertex2f(float x, float y);
  int renderVertex3f(float x, float y, float z);
  int renderVertex2d(double x, double y);
  int renderVertex3d(double x, double y, double z);

  /* Transformation */
  int translatef(float x, float y, float z);
  int translated(double x, double y, double z);

  int rotatef(float angle, float x, float y, float z);
  int rotated(double angle, double x, double y, double z);
  int rotatef(float x, float y, float z);
  int rotated(double x, double y, double z);

  int scalef(float x, float y, float z);
  int scaled(double x, double y, double z);

  /* Matrix */
  int matrix(int matrix);

  /* Viewport */
  int viewport(int x, int y, unsigned int width, unsigned int height);
  int ortho(double left, double right, double bottom, double top, double znear, double zfar);
  int frustum(double left, double right, double bottom, double top, double znear, double zfar);
  int perspective(double left, double right, double bottom, double top, double znear, double zfar);

  /* Other Stuff */
  int loadIdentity();
  int cullFace(int face);

};

#endif
