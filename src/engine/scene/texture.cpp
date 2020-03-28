#include "scene.h"
#include "../renderer/renderer_api.h"

#include <iostream> // remove

extern renderer_api* rendererApi;

void me::wcolor::bind()
{
  if (type==ME_WCOLOR_TYPE_IMAGE)
    rendererApi->bindImage(image);
  else if (type==ME_WCOLOR_TYPE_RGBA)
    rendererApi->color(rgba->x, rgba->y, rgba->z, rgba->w);
  else if (type==ME_WCOLOR_TYPE_FLOAT)
    rendererApi->color(v_float, v_float, v_float, 1.0F);
}

void me::wcolor::unbind()
{
  if (type==ME_WCOLOR_TYPE_IMAGE)
    rendererApi->unbindImage();
}
