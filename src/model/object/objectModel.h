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
 * @brief Concrete `Object` class
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
private:
    SIZE _altitude = 0; // 0 ~ 255
    std::unique_ptr<ObjectView> _view;
};


} // AGE


#endif
