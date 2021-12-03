#include "cameraView.h"

#include "object/objectView.h"
#include "../controller/adapter/ncurseAdapter.h"
#include "../model/object/objectModel.h"

namespace AGE
{

CameraView::CameraView(WindowWithCamera &model): View {}, _model {model} {}

CameraView::~CameraView() {}

void CameraView::draw(Ncurses::Window &win)
{
    // try to draw the border on the screen
    if (_model._hasBorder) {
        win.showBorder(
            _model._topBorder, _model._bottomBorder, 
            _model._leftBorder, _model._rightBorder, _model._cornerBorder
        );
    }
    
    // sort every `ObjectModel` by its depth
    std::priority_queue<const Object *, std::vector<const Object *>, ObjectCompareAltitude> pq;
    size_t i = 0;
    for (i = 0; i < _model._collidables.size(); ++i) {
        pq.push(_model._collidables[i].get());
    }
    for (i = 0; i < _model._nonCollidables.size(); ++i) {
        pq.push(_model._nonCollidables[i].get());
    }
    
    // draw each stored `Object`
    while (!pq.empty()) {
        const Object *obj = pq.top();
        obj->getView().draw(win);
        pq.pop();
    }

    // refresh this window buffer to show the actual changes
    win.refresh();
}

void CameraView::update(Ncurses::Window &win)
{

}

} // AGE

