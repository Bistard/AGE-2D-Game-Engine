/*******************************************************************************
 * @file ageEngine.h
 * @author Sihan Li (lshh1015813038@gmail.com)
 * @brief They entry header file for the AGE engine.
 * @version 0.1
 * @date 2021-11-27
 ******************************************************************************/

#ifndef __AGE_AGE_ENGINE__
#define __AGE_AGE_ENGINE__

#include <memory>
#include "common/box.h"
#include "common/point.h"
#include "common/velocity.h"

#include "controller/adapter/ncurseAdapter.h"
#include "controller/controller.h"
#include "controller/curseController.h"

#include "model/window/windowModel.h"
#include "model/window/gameWindow.h"
#include "model/window/statusWindow.h"
#include "model/window/boardWindow.h"

#include "view/view.h"
#include "view/statusView.h"
#include "view/cameraView.h"

#include "utils/timer.h"
#include "utils/camera.h"

#ifndef AGE_DEFAULT_FPS
    #define AGE_DEFAULT_FPS 2
#endif

#ifndef AGE_ENHANCED_FPS
    #define AGE_ENHANCED_FPS 60
#endif

#ifndef AGE_INPUT_ERR
    #define AGE_INPUT_ERR ERR
#endif

#define AGE_DEFAULT_WIN_WIDTH 80
#define AGE_DEFAULT_WIN_HEIGHT 25

namespace AGE
{

/*******************************************************************************
 * @brief The entry for the engine - client needs to inherit from this class.
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
     * @brief default AGE engine layout with default Window Settings.
     *              GameWindow 
     *            ↙          ↘
     *      BoardWindow    StatusWindow
     */
    AgeEngine(int fps, size_t width = AGE_DEFAULT_WIN_WIDTH, size_t height = AGE_DEFAULT_WIN_HEIGHT)
    {
        // 设置console大小
        
        std::unique_ptr<GameWindow> win = makeGameWindow(fps, {1, 1}, width, height);
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
    AgeEngine(std::unique_ptr<WindowWithController> &&win): _mainWindow {std::move(win)} {}
    
    virtual ~AgeEngine() {}

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

    virtual void init() { /* empty body. Client need to override. */ }
    virtual void onEachFrame() { /* empty body. Client need to override. */ }

    /**
     * @brief actual inner game loop that controls every detail in each frame.
     * Client can only control the game logic for each frame.
     */
    void __game_loop()
    {
        this->init();
    
        _mainWindow->drawViews();

        while (true) {

            int in = _mainWindow->getInput();
        
            // game logic function, overrides by the user.
            this->onEachFrame();

            // TODO: this->updateGameLogic();

            _mainWindow->updateViews();

            // must be invoked as the end of the loop inorder to let the program 
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
