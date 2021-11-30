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
#include <queue>

namespace AGE
{

namespace Ncurses { 
    class Window; 
}
template<typename T> class Point;
class Controller;
class View;
class Camera;

/*******************************************************************************
 * @brief Base Class - `Model` component in MVC which controls window's logic.
 ******************************************************************************/
class WindowModel
{
public:
    WindowModel(Point<int> pos, size_t width, size_t height);
    virtual ~WindowModel();
public:
    void drawViews() const;
    void updateViews() const;
    void cleanViews();
protected:
    View &addView(std::unique_ptr<View> &&view);
    View &detechView(std::unique_ptr<View> &&view);
    WindowModel &addSubWindow(std::unique_ptr<WindowModel> &&window);
    WindowModel &detachSubWindow(std::unique_ptr<WindowModel> &&window);
private:
    std::vector<std::unique_ptr<View>> _views;
    std::vector<std::unique_ptr<WindowModel>> _subWindowModels;
};


/*******************************************************************************
 * @brief Virtual Derived Class
 ******************************************************************************/
class WindowWithController: virtual public WindowModel
{
public:
    WindowWithController(Point<int> pos, size_t width, size_t height);
    WindowWithController(Point<int> pos, size_t width, size_t height, std::unique_ptr<Controller> &&controller);
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
    WindowWithCamera(Point<int> pos, size_t width, size_t height);
    ~WindowWithCamera() override;
public:
    const Camera &getCamera() const;
    // void addObject(std::unique_ptr<ObjectModel> &&object);
    // void detachObject(std::unique_ptr<ObjectModel> &&object);
private:
    std::unique_ptr<Camera> _camera;
    // std::vector<std::unique_ptr<NonCollidableObject>> _objects;
    // std::vector<std::unique_ptr<CollidableObject>> _objects;
};

} // AGE

#endif
