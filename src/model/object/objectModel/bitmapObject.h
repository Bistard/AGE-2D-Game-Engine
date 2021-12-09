/**
 * @file bitmapObject.h
 * @author Sihan Li (lshh1015813038@gmail.com)
 * @version 0.1
 * @date 2021-12-04
 */

#ifndef __AGE_BITMAP_OBJECT__
#define __AGE_BITMAP_OBJECT__

#include "../objectModel.h"
#include "../../../utils/bitmap.h"

namespace AGE
{

/*******************************************************************************
 * @brief Concrete `ObjectModel` class - specified by a vector of (x, y, char) 
 *  triples.
 ******************************************************************************/
class BitmapObject : public ObjectModel
{
public:
    BitmapObject();
    ~BitmapObject() override;
private:

};

} // AGE



#endif
