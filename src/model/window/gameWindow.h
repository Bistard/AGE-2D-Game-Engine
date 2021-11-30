/**
 * @file gameWindow.h
 * @author Sihan Li (lshh1015813038@gmail.com)
 * @brief one of default WindowModel provied by the AGE engine.
 * @version 0.1
 * @date 2021-11-28
 */

#ifndef __AGE_GAME_WINDOW__
#define __AGE_GAME_WINDOW__

#include "windowModel.h"

namespace  AGE
{

class StatusWindow;
class BoardWindow;
class GameWindow;
template<typename T> 
class Point;

/**
 * @brief A helper function to create a GameWindow (the default AGE engine game layout).
 * This is the ONLY valid way to construct a GameWindow type.
 */
std::unique_ptr<GameWindow> makeGameWindow(int FPS, Point<int> pos, size_t width, size_t height);

class GameWindow : public WindowWithController
{
public:
    GameWindow(int FPS, Point<int> pos, size_t width, size_t height, 
        std::unique_ptr<StatusWindow> &&statusWin, 
        std::unique_ptr<BoardWindow> &&boardWin);
    ~GameWindow() override;
public:
    StatusWindow &getStatusWindow();
    BoardWindow &getBoardWindow();
private:
    StatusWindow &_statusWindow;
    BoardWindow &_boardWindow;
};

} // AGE

#endif

