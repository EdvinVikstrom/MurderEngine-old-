#ifndef RENDER_HELPER_H
  #define RENDER_HELPER_H

void render_rectangle(unsigned int color, double x, double y, double width, double height, bool fill);
void render_lozenge(unsigned int color, double x, double y, double width, double height, bool fill);

void render_get_point_in_curve(me::vec2d* points, int offset, int length, double t, ::vec2d* output);
void render_bezier(me::vec2d* points, double resolution, bool adaptive, int mode, int off, int len);
void render_text(const char* text, double x, double y, unsigned int font, unsigned int fontSize);

void render_enable_smooth_line();
void render_disable_smooth_line();

void render_line_width(float width);
void render_color(unsigned int color);

void render_start();
void render_end();

#endif
