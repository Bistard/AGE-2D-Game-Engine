/**
 * @file objectView.h
 * @author Sihan Li (lshh1015813038@gmail.com)
 * @version 0.1
 * @date 2021-12-02
 */

#ifndef __AGE_OBJECT_VIEW__
#define __AGE_OBJECT_VIEW__

#include "../view.h"
#include "../../model/object/objectModel.h"
#include "../../controller/adapter/ncurseAdapter.h"

namespace AGE
{

/*******************************************************************************
 * @brief Abstract Class
 ******************************************************************************/
class ObjectView : public View
{
public:
    ObjectView(ObjectModel &obj): View {}, _obj {obj} {}
    ~ObjectView() override {}
protected:
    ObjectModel &_obj;
};

} // AGE


#endif
