#include "cameraView.h"
#include "../controller/adapter/ncurseAdapter.h"
#include "../model/window/windowModel.h"

namespace AGE
{

CameraView::CameraView(WindowWithCamera &model): 
    View {}, 
    _window { Ncurses::newWindow(model.width, model.height, model.position.X(), model.position.Y()) },
    _model {model}
{}

CameraView::~CameraView() {}

void CameraView::draw() 
{
    if (_model._hasBorder) {
        _window->showBorder(_model._topBorder, _model._bottomBorder, _model._leftBorder, 
            _model._rightBorder, _model._cornerBorder);    
    }
    
}

void CameraView::update()
{

}

void CameraView::clear()
{
    
}

} // AGE
