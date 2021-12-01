#include "../../common/point.h"
#include "windowModel.h"
#include "../../controller/controller.h"
#include "../../view/view.h"
#include "../../view/cameraView.h"
#include "../../utils/camera.h"

namespace AGE
{

/*******************************************************************************
 * @brief `WindowModel` implementation
 ******************************************************************************/

WindowModel::WindowModel(Point<int> pos, SIZE width, SIZE height): 
    position {pos}, width {width}, height {height} 
{}

WindowModel::~WindowModel() {}

void WindowModel::drawViews() const
{
    for (auto &win : _subWindowModels) {
        win->drawViews();
    }
    
    for (auto &v : _views) {
        v->draw();
    }
}

void WindowModel::updateViews() const
{
    for (auto &win : _subWindowModels) {
        win->updateViews();
    }

    for (auto &v : _views) {
        v->update();
    }
}

void WindowModel::cleanViews()
{
    _views.clear();
}

View &WindowModel::addView(std::unique_ptr<View> &&view)
{
    View &ref = *view;
    _views.emplace_back( std::move(view) );
    return ref;
}

View &WindowModel::detechView(std::unique_ptr<View> &&view)
{
    // TODO
}

WindowModel &WindowModel::addSubWindow(std::unique_ptr<WindowModel> &&window)
{
    WindowModel &ref = *window;
    _subWindowModels.emplace_back( std::move(window) );
    return ref;
}

WindowModel &detachSubWindow(std::unique_ptr<WindowModel> &&window)
{
    // TODO
}

/*******************************************************************************
 * @brief `WindowWithController` implementation
 ******************************************************************************/

WindowWithController::WindowWithController(Point<int> pos, SIZE width, SIZE height): WindowModel {pos, width, height}, _controller {nullptr} {}

WindowWithController::WindowWithController(Point<int> pos, SIZE width, SIZE height, std::unique_ptr<Controller> &&controller): 
    WindowModel {pos, width, height}, 
    _controller {std::move(controller)} 
{}

WindowWithController::~WindowWithController() {}

int 
WindowWithController::getInput() const { return _controller->getInput(); }

void 
WindowWithController::setController(std::unique_ptr<Controller> &&c) { _controller = std::move(c); }

Controller &
WindowWithController::getController() const { return *_controller; }

/*******************************************************************************
 * @brief `WindowWithCamera` implementation
 ******************************************************************************/
WindowWithCamera::WindowWithCamera(Point<int> pos, SIZE width, SIZE height): WindowModel {pos, width, height}
{
    // construction of `WindowWithCamera` will auomatically add a `CameraView` into the vector.
    this->addView( std::make_unique<CameraView>(*this) );
    _camera = std::make_unique<Camera>(pos, width, height);
}

WindowWithCamera::~WindowWithCamera() {}

const Camera &
WindowWithCamera::getCamera() const { return *_camera; }

void 
WindowWithCamera::setBorder(bool show, int top, int bottom, int left, int right, int corner)
{
    _hasBorder = show;

    _topBorder = top;
    _bottomBorder = bottom;
    _leftBorder = left;
    _rightBorder = right;
    _cornerBorder = corner;
}

} // AGE

