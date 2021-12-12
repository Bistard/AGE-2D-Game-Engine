/*******************************************************************************
 * @file ageEngine.h
 * @author Sihan Li (lshh1015813038@gmail.com)
 * @brief They entry header file for the AGE engine.
 * @version 0.2
 * @date 2021-12-04
 ******************************************************************************/

#ifndef __AGE_AGE_ENGINE__
#define __AGE_AGE_ENGINE__

#include <memory>
#include "common/box.h"
#include "common/vec2d.h"

#include "controller/adapter/ncurseAdapter.h"
#include "controller/controller.h"
#include "controller/curseController.h"

#include "model/window/windowModel.h"
#include "model/window/gameWindow.h"
#include "model/window/statusWindow.h"
#include "model/window/boardWindow.h"

#include "model/registry/registry.h"
#include "model/registry/scene.h"

#include "model/component/component.h"
#include "model/component/gravity.h"
#include "model/component/position.h"
#include "model/component/renderer.h"
#include "model/component/texture.h"
#include "model/component/velocity.h"
#include "model/component/collidable.h"

#include "model/entity/entity.h"

#include "model/system/system.h"
#include "model/system/motionSystem.h"
#include "model/system/collisionSystem.h"
#include "model/system/renderSystem.h"

#include "utils/timer.h"
#include "utils/camera.h"
#include "utils/math.h"
#include "utils/uuid.h"

namespace AGE
{

/*******************************************************************************
 * @brief Abstract Class - The entry for the engine - client needs to inherit from here.
 * 
 *   Clients need to override two private virtual functions when inheriting.
 *     - `init()`: will be invoked before the actual game loop.
 *     - `onEachFrame()`: will be invoked for each game frame.
 * 
 * @details Instead of the default game layout. Clients may provide their own
 *   customized `WindowModelWithController` to change it.
 ********************************************************************************/
template<std::intmax_t FPS = AGE_DEFAULT_FPS>
class AgeEngine
{

public:

    /**
     * @brief default AGE engine layout with default WindowBuffer Settings.
     *              GameWindow
     *            ↙          ↘
     *      BoardWindow    StatusWindow
     */
    AgeEngine(int fps, SIZE width = AGE_DEFAULT_WIN_WIDTH, SIZE height = AGE_DEFAULT_WIN_HEIGHT)
    {
        __init_curses(width, height);
        
        // StatusWindow has 3 rows height. 
        // BoardWindow with 22 rows height. 20 rows height without boarder.
        std::unique_ptr<GameWindow> win = 
            makeGameWindow(fps, {0, 0}, width, height, {0, height - 3}, width, 3, {0, 0}, width, height - 3);
        _mainWindow = std::move(win);
    }

    /**
     * @brief for clients to customize the engine layout with their provided WindowModel.
     *            CustomizeWindow 
     *            ↙          ↘
     *         ...              ...
     *        ↙ ↘             ↙ ↘
     *     ...    ...         ...  ...
     */
    AgeEngine(int fps, SIZE width, SIZE height, std::unique_ptr<WindowWithController> &&win)
    {
        __init_curses(width, height);
        _mainWindow = std::move(win);
    }
    
    virtual ~AgeEngine() 
    {
        // deallocates memory and ends ncurses
        Ncurses::destroy();
    }

public:

    WindowWithController &getWindow() { return *_mainWindow; }
    WindowWithController &setWindow(std::unique_ptr<WindowWithController> &&win) 
    { 
        WindowWithController &ref = *win;
        _mainWindow = std::move(win); 
        return ref;
    }

    /* runs the game loop. */
    void run() { __game_loop(); }

private:

    void __init_curses(SIZE width, SIZE height)
    {
        // sets up memory for ncurses
        Ncurses::init(Ncurses::WindowOpt::CBREAK, false);
        // set the cursor invisible
        Ncurses::setCursorVisibility(Ncurses::CurseVisibility::INVISIBLE);
    }

    virtual void init() = 0;
    virtual void onEachFrame(int input) = 0;

    /**
     * @brief actual inner game loop that controls every detail in each frame.
     * Client can only control the game logic for each frame.
     */
    void __game_loop()
    {
        this->init();

        _mainWindow->drawViews();

        while (true) { // TODO: consider using do...while

            int input = _mainWindow->getInput();
            
            // game logic function, overrides by the user.
            this->onEachFrame(input);

            _mainWindow->updateLogics();

            _mainWindow->drawViews();

            // must be invoked at the end of the loop in order to let the program 
            //   pause utill the next frame.
            _timer.tick();
        }
    }
private:
    // the timer controls the refresh frame rate
    Timer<FPS> _timer;

    /**
     * @brief The entire window of the engine (might be composed with subwindows)
     * 
     * If the AGE engine is constructed using default constructor (no provide window), 
     *  this is a unique_ptr to `GameWindow` type. You can static_cast<GameWindow> 
     *  to get the `GameWindow`.
     */
    std::unique_ptr<WindowWithController> _mainWindow;
};

} // AGE

#endif
