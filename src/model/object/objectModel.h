/**
 * @file objectModel.h
 * @author Sihan Li (lshh1015813038@gmail.com)
 * @version 0.2
 * @date 2021-12-03
 */

#ifndef __AGE_OBJECT_MODEL__
#define __AGE_OBJECT_MODEL__

#include "object.h"

namespace AGE
{

class ObjectView;

/*******************************************************************************
 * @brief Abstract `Object` class
 * 
 * Each concrete `ObjectModel` class should constructs its own `ObjectView` type. 
 *  Such an `ObjectView` determines HOW to draw the object onto the window buffer.
 ******************************************************************************/
class ObjectModel : public Object
{
public:
    ObjectModel(std::unique_ptr<ObjectView> &&view);
    virtual ~ObjectModel();
public:
    SIZE getAltitude() const noexcept override;
    void setAltitude(char val) override;
    ObjectView &getView() const noexcept override; 
    /* virtual vec2d<float> &getPosition() = 0; */
private:
    SIZE _altitude = 0; // 0 ~ 255
    std::unique_ptr<ObjectView> _view;
};


} // AGE


#endif
