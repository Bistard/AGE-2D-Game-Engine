#include "../../common/vec2d.h"
#include "windowModel.h"
#include "../../controller/controller.h"
#include "../../utils/camera.h"

namespace AGE
{

/*******************************************************************************
 * @brief `WindowModel` implementation
 ******************************************************************************/

WindowModel::WindowModel(vec2d<int> pos, SIZE width, SIZE height): 
    position {pos}, width {width}, height {height} 
{}

WindowModel::~WindowModel() {}

WindowModel &WindowModel::addSubWindow(std::unique_ptr<WindowModel> &&window)
{
    WindowModel &ref = *window;
    _subWindowModels.push_back( std::move(window) );
    return ref;
}

// WindowModel &detachSubWindow(std::unique_ptr<WindowModel> &&window)
// {
//     // TODO
// }

void WindowModel::drawViews()
{
    for (auto &win : _subWindowModels) {
        win->drawViews();
    }
    this->onDrawView();
}

void WindowModel::updateLogics()
{
    for (auto &win : _subWindowModels) {
        win->updateLogics();
    }
    this->onUpdateLogic();
}

/*******************************************************************************
 * @brief `WindowWithController` implementation
 ******************************************************************************/

WindowWithController::WindowWithController(vec2d<int> pos, SIZE width, SIZE height): 
    WindowModel {pos, width, height}, _controller {nullptr} 
{}

WindowWithController::WindowWithController(vec2d<int> pos, SIZE width, SIZE height, std::unique_ptr<Controller> &&controller): 
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
WindowWithCamera::WindowWithCamera(vec2d<int> pos, SIZE width, SIZE height): 
    WindowModel {pos, width, height}, 
    _winBuffer { std::make_unique<Ncurses::WindowBuffer>(width, height, position.X(), position.Y()) },
    _scene {}
{
    _camera = std::make_unique<Camera>(pos, width, height);
}

WindowWithCamera::~WindowWithCamera() {}

Camera &
WindowWithCamera::getCamera() noexcept { return *_camera; }

Scene &
WindowWithCamera::getScene() noexcept { return _scene; }

Ncurses::WindowBuffer &
WindowWithCamera::getWindowBuffer() noexcept { return *_winBuffer; }

void 
WindowWithCamera::onDrawView()
{
    _scene.updateViewSystems();
}

void 
WindowWithCamera::onUpdateLogic()
{
    _scene.updateLogicSystems();
}

} // AGE

