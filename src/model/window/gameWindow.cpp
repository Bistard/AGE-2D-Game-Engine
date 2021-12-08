#include "../../controller/curseController.h"
#include "gameWindow.h"
#include "statusWindow.h"
#include "boardWindow.h"
// #include "../../common/vec2d.h"

namespace AGE
{

std::unique_ptr<GameWindow> 
makeGameWindow(int FPS, 
    vec2d<int> pos, SIZE width, SIZE height, 
    vec2d<int> pos1, SIZE width1, SIZE height1, 
    vec2d<int> pos2, SIZE width2, SIZE height2)
{
    std::unique_ptr<StatusWindow> statusWin = std::make_unique<StatusWindow>(pos1, width1, height1);
    std::unique_ptr<BoardWindow> boardWin = std::make_unique<BoardWindow>(pos2, width2, height2);
    std::unique_ptr<GameWindow> gameWin = 
        std::make_unique<GameWindow>(FPS, pos, width, height, std::move(statusWin), std::move(boardWin));
    return gameWin;
}

GameWindow::GameWindow(int FPS, vec2d<int> pos, SIZE width, SIZE height, 
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

