/**
 * @file system.h
 * @author Sihan Li (lshh1015813038@gmail.com)
 * @version 0.1
 * @date 2021-12-11
 */

#ifndef __AGE_SYSTEM__
#define __AGE_SYSTEM__

namespace AGE
{

/**
 * @brief An interface for all the systems in the ECS.
 * 
 * A `System` only handles all the logics in the ECS. It queries all the 
 * `Component` from ECS where the data is stored. And perform some certain 
 * logic based or to the data itself.
 */
class ISystem
{
public:
    virtual void onUpdate() = 0;
};

} // AGE


#endif
