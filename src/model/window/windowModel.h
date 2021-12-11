/**
 * @file windowModel.h
 * @author Sihan Li (lshh1015813038@gmail.com)
 * @brief 
 * @version 0.5
 * @date 2021-12-08
 */

#ifndef __AGE_WINDOW_MODEL__
#define __AGE_WINDOW_MODEL__

#include <vector>
#include <list>
#include <memory>

#include "../../utils/math.h"
#include "../registry/scene.h"

namespace AGE
{

namespace Ncurses { 
    class Window; 
}
template<typename T> class vec2d;
class Controller;
class Camera;

/*******************************************************************************
 * @brief Base Class - `Model` component in MVC which controls window's logic.
 ******************************************************************************/
class WindowModel
{
public:
    WindowModel(vec2d<int> pos, SIZE width, SIZE height);
    virtual ~WindowModel();
public:
    WindowModel &addSubWindow(std::unique_ptr<WindowModel> &&window);
    WindowModel &detachSubWindow(std::unique_ptr<WindowModel> &&window);

    /**
     * @brief Recursively draws all the views from subwindows first. The 
     *  derived classes controls the behaviours of drawing by overriding the 
     *  belowing private virtual method `onDrawView()`.
     */
    void drawViews() const;

    /**
     * @brief Recursively updates all the game logics from subwindows first. The
     *  derived classes controls the behaviours of updating logics by overriding
     *  the belowing private virtual method `onUpdateLogic()`.
     */
    void updateLogics();
private:
    virtual void onDrawView() const {}
    virtual void onUpdateLogic() {}
protected:
    const vec2d<int> position;
    const SIZE width;
    const SIZE height;
private:
    std::vector<std::unique_ptr<WindowModel>> _subWindowModels;
};

/*******************************************************************************
 * @brief Virtual Derived Class
 ******************************************************************************/
class WindowWithController: virtual public WindowModel
{
public:
    WindowWithController(vec2d<int> pos, SIZE width, SIZE height);
    WindowWithController(vec2d<int> pos, SIZE width, SIZE height, std::unique_ptr<Controller> &&controller);
    ~WindowWithController() override;
public:
    // get users input directly from the built-in controller
    int getInput() const;
    void setController(std::unique_ptr<Controller> &&c);
    Controller &getController() const;
private:
    std::unique_ptr<Controller> _controller;
};


/*******************************************************************************
 * @brief Virtual Derived Class
 ******************************************************************************/
class WindowWithCamera: virtual public WindowModel
{
public:
    WindowWithCamera(vec2d<int> pos, SIZE width, SIZE height);
    ~WindowWithCamera() override;
public:
    Camera &getCamera() noexcept;
    Scene &getScene() noexcept;
    Ncurses::Window &getWindowBuffer() noexcept;
private:
    void onDrawView() const override;
    void onUpdateLogic() override;
private:
    /** @brief gives data access to `CameraView` makes everything so much easier */
    friend class CameraView;

    /** @brief window buffer for `View` to output */
    std::unique_ptr<Ncurses::Window> _winBuffer;
    std::unique_ptr<Camera> _camera;

    /** @brief maintains the main functionality of the window content */
    Scene _scene;
};

} // AGE

#endif
