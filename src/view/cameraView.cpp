#include "cameraView.h"

#include "object/objectView.h"
#include "../controller/adapter/ncurseAdapter.h"
#include "../model/object/objectModel.h"

namespace AGE
{

CameraView::CameraView(WindowWithCamera &model): View {}, _model {model} {}

CameraView::~CameraView() {}

void CameraView::draw(Ncurses::Window &winBuff)
{
    winBuff.erase();

    // try to draw the border on the screen
    if (_model._hasBorder) {
        winBuff.showBorder(
            _model._topBorder, _model._bottomBorder, 
            _model._leftBorder, _model._rightBorder, _model._cornerBorder
        );
    }
    
    // sort every `ObjectModel` by its depth (smallest altitude on the top)
    std::priority_queue<const Object *, std::vector<const Object *>, ObjectCompareAltitude> pq;
    std::shared_ptr<Collidable> access1;
    std::shared_ptr<NonCollidable> access2;
    size_t i = 0;

    for (i = 0; i < _model._collidables.size(); ++i) {
        if (_model._collidables[i].expired() == true) {
            // TODO: remove this weak_ptr from the vector
            continue;
        }
        access1 = _model._collidables[i].lock();
        pq.push(access1.get());
    }
    for (i = 0; i < _model._nonCollidables.size(); ++i) {
        if (_model._nonCollidables[i].expired() == true) {
            // TODO: remove this weak_ptr from the vector
            continue;
        }
        access2 = _model._nonCollidables[i].lock();
        pq.push(access2.get());
    }
    
    // draw each `Object` by their altitude (from the furthest to closest)
    while (!pq.empty()) {
        const Object *obj = pq.top();
        obj->getView().draw(winBuff);
        pq.pop();
    }

    // refresh this window buffer to show the actual changes
    winBuff.refresh();
}

} // AGE

