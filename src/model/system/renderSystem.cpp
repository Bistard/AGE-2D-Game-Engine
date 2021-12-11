#include "renderSystem.h"
#include "../../controller/adapter/ncurseAdapter.h"
#include "../registry/registry.h"
#include "../component/render.h"
#include "../component/border.h"


namespace AGE
{

RenderSystem::RenderSystem(Registry &registry, Ncurses::Window &winBuffer): ViewSystem {registry}, _winBuffer {winBuffer} {}

RenderSystem::~RenderSystem() {}

void RenderSystem::onUpdate()
{
    // cleans the window buffer
    _winBuffer.erase();

    // displays border
    try {
        auto &border = _registry.queryGlobal<CGlobalBorder>();
        _winBuffer.showBorder(border.top, border.bottom, border.left, border.right, border.corner);
    } catch (...) {

    }

    auto entities = _registry.query<CRender>()[0];
    // TODO: this is where the `CameraView` does the job

    // refresh the window buffer to show the actual frame
    _winBuffer.refresh();
}

} // AGE
