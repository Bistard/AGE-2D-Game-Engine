/**
 * @file windowModel.h
 * @author Sihan Li (lshh1015813038@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-11-28
 */

#ifndef __AGE_WINDOW_MODEL__
#define __AGE_WINDOW_MODEL__

#include <vector>
#include <memory>
#include "../../utils/math.h"

namespace AGE
{

namespace Ncurses { 
    class Window; 
}
template<typename T> class Point;
class Controller;
class Camera;
class CameraView;

class Collidable;
class NonCollidable;

/*******************************************************************************
 * @brief Base Class - `Model` component in MVC which controls window's logic.
 ******************************************************************************/
class WindowModel
{
public:
    WindowModel(Point<int> pos, SIZE width, SIZE height);
    virtual ~WindowModel();
public:
    WindowModel &addSubWindow(std::unique_ptr<WindowModel> &&window);
    WindowModel &detachSubWindow(std::unique_ptr<WindowModel> &&window);

    /**
     * @brief These functions will recursively draw all the views from subwindows 
     *  first. If the derived classes provide new `View`, they need to override
     *  the following private virtual methods.
     */
    void drawViews() const;
    void updateViews() const;
    void clearViews();
private:
    virtual void drawView() const {}
    virtual void updateView() const {}
protected:
    const Point<int> position;
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
    WindowWithController(Point<int> pos, SIZE width, SIZE height);
    WindowWithController(Point<int> pos, SIZE width, SIZE height, std::unique_ptr<Controller> &&controller);
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
    WindowWithCamera(Point<int> pos, SIZE width, SIZE height);
    ~WindowWithCamera() override;
public:
    // default value: 32 -> blanks space
    void setBorder(bool show, int top = 32, int bottom = 32, int left = 32, int right = 32, int corner = 32);
    const Camera &getCamera() const;
    
    CameraView &addView(std::unique_ptr<CameraView> &&view);
    CameraView &detechView(std::unique_ptr<CameraView> &&view);

    void addObject(std::shared_ptr<Collidable> &obj);
    void addObject(std::shared_ptr<NonCollidable> &obj);
private:
    void drawView() const override;
    void updateView() const override;
private:
    // give data access to `CameraView` makes everything so much easier
    friend class CameraView;

    // window buffer for `View` to output
    std::unique_ptr<Ncurses::Window> _winBuffer;

    std::unique_ptr<Camera> _camera;
    std::unique_ptr<CameraView> _cameraview;
    
    /**
     * @brief Usage of std::
     */
    std::vector<std::weak_ptr<Collidable>> _collidables;
    std::vector<std::weak_ptr<NonCollidable>> _nonCollidables;

    bool _hasBorder;
    int _topBorder, _bottomBorder, _leftBorder, _rightBorder, _cornerBorder;
};

} // AGE

#endif
