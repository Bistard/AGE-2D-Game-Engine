/**
 * @file statusWindow.h
 * @author Sihan Li (lshh1015813038@gmail.com)
 * @brief one of default WindowModel provied by the AGE engine.
 * @version 0.1
 * @date 2021-11-28
 */

#ifndef __AGE_STATUS_WINDOW__
#define __AGE_STATUS_WINDOW__

#include "windowModel.h"
#include "../../view/statusView.h"

namespace AGE
{

class StatusWindow : public WindowWithCamera
{
public:
    StatusWindow(Point<int> pos, SIZE width, SIZE height): 
        WindowModel {pos, width, height},
        WindowWithCamera {pos, width, height}
    {}
    ~StatusWindow() override {}
public:
    // StatusView &addStatusView(std::unique_ptr<StatusView> &&statusView) 
    // {
    //     return static_cast<StatusView &>(this->addView(std::move(statusView))); // FIX ME
    // }
};

} // AGE


#endif
