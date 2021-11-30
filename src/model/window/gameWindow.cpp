#include "../../controller/curseController.h"
#include "gameWindow.h"
#include "statusWindow.h"
#include "boardWindow.h"
// #include "../../common/point.h"

namespace AGE
{

std::unique_ptr<GameWindow> 
makeGameWindow(int FPS, Point<int> pos, size_t width, size_t height)
{
    std::unique_ptr<StatusWindow> statusWin = std::make_unique<StatusWindow>(pos, width, height);
    std::unique_ptr<BoardWindow> boardWin = std::make_unique<BoardWindow>(pos, width, height);
    std::unique_ptr<GameWindow> gameWin = 
        std::make_unique<GameWindow>(FPS, pos, width, height, std::move(statusWin), std::move(boardWin));
    return gameWin;
}

GameWindow::GameWindow(int FPS, Point<int> pos, size_t width, size_t height, 
    std::unique_ptr<StatusWindow> &&statusWin, 
    std::unique_ptr<BoardWindow> &&boardWin): 
        WindowModel {pos, width, height},
        WindowWithController {pos, width, height},
        _statusWindow { *statusWin },
        _boardWindow { *boardWin }
{
    this->setController( std::make_unique<CurseController>(FPS) );
    this->addSubWindow( std::move(statusWin) );
    this->addSubWindow( std::move(boardWin) );
}

GameWindow::~GameWindow() {}

StatusWindow &
GameWindow::getStatusWindow() { return _statusWindow; }

BoardWindow &
GameWindow::getBoardWindow() { return _boardWindow; }

} // AGE

