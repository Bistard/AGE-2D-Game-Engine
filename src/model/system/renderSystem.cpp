#include "renderSystem.h"
#include "../../controller/adapter/ncurseAdapter.h"
#include "../registry/registry.h"
#include "../component/renderer.h"
#include "../component/global/border.h"
#include "../component/despawn.h"

#include <queue>

namespace AGE
{

RenderSystem::RenderSystem(Registry &registry, Ncurses::WindowBuffer &winBuffer): ViewSystem {registry}, _winBuffer {winBuffer} {}

RenderSystem::~RenderSystem() {}

void RenderSystem::onUpdate()
{
    // cleans the window buffer
    _winBuffer.erase();

    // displays border
    try {
        auto &border = _registry.queryGlobal<CBorderView>();
        if (border.visible == true) {
            _winBuffer.showBorder(border.top, border.bottom, border.left, border.right, border.corner);
        }
    } catch (...) {
        // no border
    }

    // sorts each `CRenderer` based on its altitude.
    std::priority_queue<CRenderer *, std::vector< CRenderer *>, CRendererCompare> pq;
    auto [entities] = _registry.query<CRenderer>();

    for (auto &entity : entities)  {
        auto &renderer = _registry.get<CRenderer>(*entity);

        if (renderer.visible == true) {
            pq.push(&renderer);
        }
    }

    // iterate all the `CRenderer` components and draws them on the window buffer.
    CRenderer *renderer = nullptr;
    
    while (pq.empty() == false) {
        renderer = pq.top();
        renderer->texture.paint(_winBuffer, renderer->position);
        pq.pop();
    }

    // refresh the window buffer to show the actual frame
    _winBuffer.refresh();
}

} // AGE
