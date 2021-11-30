/**
 * @file boardWindow.h
 * @author Sihan Li (lshh1015813038@gmail.com)
 * @brief one of default WindowModel provied by the AGE engine.
 * @version 0.1
 * @date 2021-11-28
 */

#ifndef __AGE_BOARD_WINDOW__
#define __AGE_BOARD_WINDOW__

#include "windowModel.h"
#include "../../view/boardView.h"

namespace AGE
{

template<typename T>
class Point;

class BoardWindow : public WindowWithCamera
{
public:
    BoardWindow(Point<int> pos, size_t width, size_t height): 
        WindowModel {pos, width, height},
        WindowWithCamera {pos, width, height}
    {}
    ~BoardWindow() override {}
public:
    BoardView &addBoardView(std::unique_ptr<BoardView> &&boardView) { return static_cast<BoardView &>(this->addView(std::move(boardView))); }
    BoardView &detachBoardView(std::unique_ptr<BoardView> &&boardView) { return static_cast<BoardView &>(this->detechView(std::move(boardView))); }
private:
    // std::unique_ptr<Grid> _grid;
    // bool _boardType;
};

} // AGE


#endif

