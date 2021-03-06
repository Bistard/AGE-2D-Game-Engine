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

class Registry;

/**
 * @brief Abstract Base Class - for all the systems in the ECS.
 * 
 * A `System` handles all the logics in the ECS. It queries all the `Component` 
 * from ECS where the data is stored. And performs some certain logic based or 
 * to the data itself.
 */
class System
{
public:
    System(Registry &registry): _registry {registry} {}
    virtual ~System() {}
public:
    virtual void onUpdate() = 0;
protected:
    Registry &_registry;
};

class LogicSystem: public System
{
public:
    LogicSystem(Registry &registry): System {registry} {}
    ~LogicSystem() override {}
public:
    void setElapse(float elapse) { _elapse = elapse; }
protected:
    float _elapse;
};

class ViewSystem: public System
{
public:
    ViewSystem(Registry &registry): System {registry} {}
    ~ViewSystem() override {}
};

} // AGE


#endif
