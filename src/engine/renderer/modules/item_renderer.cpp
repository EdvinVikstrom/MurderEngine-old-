#include "../../kernel/common/common.h"
#include "../../EngineManager.h"
#include "../renderer_api.h"
#include "../../scene/scene.h"
#include "item_renderer.h"

extern renderer_api* rendererApi;

void me::renderer::render_item(me::item* item)
{
  rendererApi->push();
  rendererApi->reset();
  rendererApi->material(item->mesh->materials->at(0));
  rendererApi->bindMesh(item->mesh);
  rendererApi->mesh(item->mesh);
  rendererApi->unbindMesh();
  rendererApi->pop();
}
