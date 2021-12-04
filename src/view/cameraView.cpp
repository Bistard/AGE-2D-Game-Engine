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
    // erase() only clean the window buffer
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
    
    for (auto it = _model._collidables.begin(); it != _model._collidables.end(); ++it) {
        
        // check validty of the object (object might got destroyed on the client side)
        if ((*it).expired() == true) {
            // allows me to erase during iteration without losing validty of the iterator
            it = _model._collidables.erase(it);
            continue;
        }
        
        access1 = (*it).lock();
        pq.push(access1.get());
    }
    for (auto it = _model._nonCollidables.begin(); it != _model._nonCollidables.end(); ++it) {
        
        if ((*it).expired() == true) {
            it = _model._nonCollidables.erase(it);
            continue;
        }

        access2 = (*it).lock();
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

