#include "../../common/vec2d.h"
#include "windowModel.h"
#include "../../controller/controller.h"
#include "../../utils/camera.h"
#include "../component/border.h"
#include "../component/boundingBox.h"
#include "../component/collidable.h"
#include "../component/position.h"


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

void WindowModel::renderViews()
{
    for (auto &win : _subWindowModels) {
        win->renderViews();
    }
    this->onDrawView();
}

void WindowModel::updateLogics(float elapse)
{
    for (auto &win : _subWindowModels) {
        win->updateLogics(elapse);
    }
    this->onUpdateLogic(elapse);
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
WindowWithCamera::onUpdateLogic(float elapse)
{
    _scene.updateLogicSystems(elapse);
}

void 
WindowWithCamera::setBorderView(bool visible, int top, int bottom, int left, int right, int corner)
{
    Registry &registry = getScene().getRegistry();
    if (registry.hasGlobal<CBorderView>() == false) {
        registry.emplaceGlobal<CBorderView>(visible, top, bottom, left, right, corner);
    }
}

void 
WindowWithCamera::setSolidBorder(bool top, bool bottom, bool left, bool right)
{
    Registry &registry = getScene().getRegistry();
    if (registry.hasGlobal<CSolidBorder>() == true) {
        return;
    }

    // If the borderView is displaying, we move the bounding box of the border
    // inside by one more pixel.
    bool visible = false;
    if (registry.hasGlobal<CBorderView>()) {
        visible = registry.queryGlobal<CBorderView>().visible;
    }
    
    // construct top solid border
    Entity *topEntity = nullptr;
    if (top) {
        topEntity = &registry.create();
        CPosition &topPosition = registry.emplace<CPosition>(*topEntity, 0, 0, 0);
        CRectBox &topBox = registry.emplace<CRectBox>(*topEntity, topPosition, width, 1);
        registry.emplace<CCollidable>(*topEntity, topBox);
    }
    
    // bottom solid border
    Entity *bottomEntity = nullptr;
    if (bottom) {
        bottomEntity = &registry.create();
        CPosition &bottomPosition = registry.emplace<CPosition>(*bottomEntity, 0, height, 0);
        CRectBox &bottomBox = registry.emplace<CRectBox>(*bottomEntity, bottomPosition, width, height);
        registry.emplace<CCollidable>(*bottomEntity, bottomBox);
    }

    // left solid border
    Entity *leftEntity = nullptr;
    if (left) {
        leftEntity = &registry.create();
        CPosition &leftPosition = registry.emplace<CPosition>(*leftEntity, 0, 0, 0);
        CRectBox &leftBox = registry.emplace<CRectBox>(*leftEntity, leftPosition, 1, height);
        registry.emplace<CCollidable>(*leftEntity, leftBox);
    }

    // right solid border
    Entity *rightEntity = nullptr;
    if (right) {
        rightEntity = &registry.create();
        CPosition &rightPosition = registry.emplace<CPosition>(*rightEntity, 0, width, 0);
        CRectBox &rightBox = registry.emplace<CRectBox>(*rightEntity, rightPosition, 1, height);
        registry.emplace<CCollidable>(*rightEntity, rightBox);
    }

    // stores them into `CSolidBorder`
    registry.emplaceGlobal<CSolidBorder>(topEntity, bottomEntity, leftEntity, rightEntity);
}

} // AGE

