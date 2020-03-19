#ifndef RENDER_PIPELINE_H
  #define RENDER_PIPELINE_H

#define RPL_TRIANGLE
#define RPL_TRIANGLE_FAN
#define RPL_LINES
#define RPL_LINE_STRIP
#define RPL_LINE_LOOP
#define RPL_QUADS
#define RPL_QUAD_STRIP
#define RPL_POINTS

#define RPL_ARGB
#define RPL_RGB

#define RPL_FLOAT
#define RPL_DOUBLE
#define RPL_CHAR
#define RPL_INT
#define RPL_UNSIGNED_INT
#define RPL_UNSIGNED_CHAR

#define RPL_TRUE
#define RPL_FALSE

#define RPL_TEXTURE_2D
#define RPL_LINE_SMOOTH

void rpl_begin(int mode);
void rpl_end();

void rpl_bind_texture(int type, int texture_id);

void rpl_enable(int opt);
void rpl_disable(int opt);

void rpl_vertex2i(int x, int y);
void rpl_vertex2f(float x, float y);
void rpl_vertex2d(double x, double y);

void rpl_vertex3i(int x, int y, int z);
void rpl_vertex3f(float x, float y, float z);
void rpl_vertex3d(double x, double y, double z);

void rpl_tex_coord2i(int x, int y);
void rpl_tex_coord2f(float x, float y);
void rpl_tex_coord2d(double x, double y);

void rpl_color3i(int r, int g, int b);
void rpl_color3f(float r, float g, float b);
void rpl_color4i(int r, int g, int b, int a);
void rpl_color4f(float r, float g, float b, float a);
void rpl_color_rgb(int rgb);
void rpl_color_argb(int argb);

void rpl_push_matrix();
void rpl_pop_matrix();

void rpl_line_width(float width);
void rpl_point_size(float size);

void rpl_viewport(int left, int right, int top, int bottom);
void rpl_ortho(int left, int right, int top, int bottom, float f_near, float f_far);

#endif
