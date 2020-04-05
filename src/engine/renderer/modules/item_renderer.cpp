#include "../../kernel/common/common.h"
#include "../../EngineManager.h"
#include "../renderer_api.h"
#include "../../scene/scene.h"
#include "item_renderer.h"

extern renderer_api* rendererApi;

void me::renderer::render_item(me::item* item)
{
  return;
  rendererApi->push();
  rendererApi->reset();
  rendererApi->transform(item->transform);
  rendererApi->bindMesh(item->mesh);
  rendererApi->mesh(item->mesh);
  rendererApi->unbindMesh();
  rendererApi->pop();
}
