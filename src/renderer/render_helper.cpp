#include <GL/glew.h>
#include <iostream>
#include "../engine/MurderEngineCommon.h"
#include "render_helper.h"

void render_get_point_in_line(double t, double p1x, double p1y, double p2x, double p2y, me::vec2d* point)
{
  point->x = p1x+((p2x-p1x)*t);
  point->y = p1y+((p2y-p1y)*t);
}

void render_rectangle(unsigned int color, double x, double y, double width, double height, bool fill)
{
  //std::cout << x << ", " << y << ", " << width << ", " << height << "\n";
  render_start();
  render_color(color);
  glBegin(GL_TRIANGLES);
  glVertex2d(x, y);
  glVertex2d(x+width, y);
  glVertex2d(x+width, y+height);
  glVertex2d(x+width, y+height);
  glVertex2d(x, y+height);
  glVertex2d(x, y);
  glEnd();
  render_end();
}

void render_lozenge(unsigned int color, double x, double y, double width, double height, bool fill)
{
    render_start();
    render_color(color);
    if (fill)
    {
        glBegin(GL_TRIANGLES);
        glVertex2d(x+(width/2), y);
        glVertex2d(x, y+(height/2));
        glVertex2d(x+width, y+(height/2));
        glVertex2d(x+(width/2), y+height);
        glVertex2d(x, y+(height/2));
        glVertex2d(x+width, y+(height/2));
    }else
    {
        glBegin(GL_LINE_LOOP);
        glVertex2d(x+(width/2), y);
        glVertex2d(x+width, y+(height/2));
        glVertex2d(x+(width/2), y+height);
        glVertex2d(x, y+(height/2));
    }
    glEnd();
    render_end();
}

me::vec2d* next = new me::vec2d[16]{
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0}
};

void render_get_point_in_curve(me::vec2d* points, int offset, int length, double t, me::vec2d* output)
{
  if (length==2)
  {
   render_get_point_in_line(t, points[0].x, points[0].y, points[1].x, points[1].y, output);
   return;
  }
  for (int i = offset; i < length-1; i++)
   render_get_point_in_line(t, points[i].x, points[i].y, points[i+1].x, points[i+1].y, &next[i]);
  render_get_point_in_curve(next, offset, length-1, t, output);
}

me::vec2d point = {0, 0};

void render_bezier(me::vec2d* points, double resolution, bool adaptive, int mode, int off, int len)
{
  if (adaptive)
  {
    me::vec2d minPos = points[0];
    me::vec2d maxPos = points[len-1];
    for (int i = 0; i < len; i++)
    {
      me::vec2d point = points[i];
      if (point.x > maxPos.x && point.y > maxPos.y)
        maxPos = point;
      else if (point.x < minPos.x && point.y < minPos.y)
        minPos = point;
    }
    double distance = minPos.distance(maxPos.x, maxPos.y);
    double f = distance*len;
    resolution = f * resolution;
  }
  glBegin(mode);
  for (double t = 0; t < 1; t+=(1.0D/resolution))
  {
    render_get_point_in_curve(points, off, len, t, &point);
    glVertex2d(point.x, point.y);
  }
  glVertex2d(points[len-1].x, points[len-1].y);
  glEnd();
}

void render_text(const char* text, double x, double y, unsigned int font, unsigned int fontSize)
{

}

void render_enable_smooth_line()
{
  glEnable(GL_LINE_SMOOTH);
}

void render_disable_smooth_line()
{
  glDisable(GL_LINE_SMOOTH);
}

void render_line_width(float width)
{
  glLineWidth(width);
}

void render_color(unsigned int color)
{
  float red = (float) ((unsigned char) (color))/255.0F;
  float green = (float) ((unsigned char) (color >> 8))/255.0F;
  float blue = (float) ((unsigned char) (color >> 16))/255.0F;
  float alpha = (float) ((unsigned char) (color >> 24))/255.0F;
  //std::cout << red << ", " << green << ", " << blue << ", " << alpha << "\n";
  glColor4f(red, green, blue, alpha);
}

void render_start()
{
  glLoadIdentity();
  glPushAttrib(GL_CURRENT_BIT);
}

void render_end()
{
  glPopAttrib();
}
