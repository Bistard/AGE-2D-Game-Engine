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

namespace AGE
{

namespace Ncurses { 
    class Window; 
}
template<typename T> class vec2d;
class Controller;
class Camera;
class CameraView;

class Object;
class ObjectDecorator;

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
     *  belowing private virtual method `drawView()`.
     */
    void drawViews() const;

    /**
     * @brief Recursively updates all the game logics from subwindows first. The
     *  derived classes controls the behaviours of updating logics by overriding
     *  the belowing private virtual method `updateLogic()`.
     */
    void updateLogics();
private:
    virtual void drawView() const {}
virtual void updateLogic() {}
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
    // default value: 32 -> blanks space
    void setBorder(bool show, int top = 32, int bottom = 32, int left = 32, int right = 32, int corner = 32);
    const Camera &getCamera() const;
    
    CameraView &addView(std::unique_ptr<CameraView> &&view);

    // void addCollidable(std::shared_ptr<Object> obj);
    void addNonCollidable(std::shared_ptr<Object> obj);

private:
    void drawView() const override;
    void updateLogic() override;
private:
    // gives data access to `CameraView` makes everything so much easier
    friend class CameraView;

    // window buffer for `View` to output
    std::unique_ptr<Ncurses::Window> _winBuffer;

    std::unique_ptr<Camera> _camera;
    std::unique_ptr<CameraView> _cameraview;

    // entt::registry reg;
    
    /**
     * @brief `WindowWithCamera` observes these `object`s. If `Object` gets 
     *  destroyed by the client side, Window will skip it when printing.
     */
    std::list<std::shared_ptr<Object>> _collidables;
    std::list<std::shared_ptr<Object>> _nonCollidables;

    bool _hasBorder;
    int _topBorder, _bottomBorder, _leftBorder, _rightBorder, _cornerBorder;
};

} // AGE

#endif
