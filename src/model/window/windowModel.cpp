#include "../../common/vec2d.h"
#include "windowModel.h"
#include "../../controller/controller.h"
#include "../../view/view.h"
#include "../../view/cameraView.h"
#include "../../utils/camera.h"
#include "../object/objectModel.h"

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

void WindowModel::drawViews() const
{
    for (auto &win : _subWindowModels) {
        win->drawViews();
    }
    this->drawView();
}

void WindowModel::updateLogics()
{
    for (auto &win : _subWindowModels) {
        win->updateLogics();
    }
    this->updateLogic();
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
    _winBuffer { std::make_unique<Ncurses::Window>(width, height, position.X(), position.Y()) }
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

CameraView &
WindowWithCamera::addView(std::unique_ptr<CameraView> &&view)
{
    CameraView &ref = *view;
    _cameraview =std::move(view);
    return ref;
}

void 
WindowWithCamera::drawView() const
{
    _cameraview->draw(*_winBuffer);
}

void 
WindowWithCamera::updateLogic()
{
    // detect collision for each `Collidable` object
    // time complexcity: O(n^2) -> O( [n(n + 1)]/2 )
    if (! _collidables.empty()) {
        
        std::shared_ptr<Collidable> obj1, obj2;

        for (auto first = _collidables.begin(); first != std::prev(_collidables.end()); ++first) {

            for (auto second = std::next(first); second != _collidables.end(); ++second) {
                
                // TODO: check validty of the pointer

                // obj1 = (*first).lock();
                // obj2 = (*second).lock();
                
                // TODO: collision detection
                
            }

        }

    } 
    
    // update each non-collidable object's data
    for (auto it = _nonCollidables.begin(); it != _nonCollidables.end(); ++it) {
        
        // check validty of the pointer
        if ((*it).unique() == true) {
            it = _nonCollidables.erase(it);
            continue;
        }
        
        // call `Object` updateData()
        (*it)->updateData();
    }
}

// void
// WindowWithCamera::addCollidable(std::shared_ptr<ObjectDecorator> obj)
// {
//     // assigning `std::shared_ptr` to `std::weak_ptr` (copy ctor)
//     _collidables.push_back( std::make_shared<Collidable>(obj) );
// }

void
WindowWithCamera::addNonCollidable(std::shared_ptr<Object> obj)
{
    _nonCollidables.push_back( obj );
}

} // AGE

