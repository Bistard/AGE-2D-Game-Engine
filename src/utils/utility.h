/**
 * @file utility.h
 * @author Sihan Li (lshh1015813038@gmail.com)
 * @version 0.1
 * @date 2021-12-15
 */


#ifndef __AGE_UTILITY__
#define __AGE_UTILITY__

#include "math.h"

namespace AGE
{

class Registry;
class Entity;

/**
 * @brief The namespace contians helper functions for quick game development. It
 * provides some default and easy choices for the client to use instead of 
 * creating their own APIs.
 */
namespace utils
{
    float randFloatNum(float range1, float range2);
    int randNum(int range1, int range2);

    namespace window
    {
        /** @brief Displays the border view (default 32 -> whitespace) */
        void setBorderView(Registry &registry, bool visible, int top = 32, int bottom = 32, int left = 32, int right = 32, int corner = 32);
        
        /** @brief Sets the border be solid */
        void setSolidBorder(Registry &registry, SIZE winWidth, SIZE winHeight, bool top, bool bottom, bool left, bool right);
        
        /** @brief Simulates the border collision response in real world */
        void setSolidBorderCollisionResponse(Registry &registry, bool enable);
    }
    
    /**
     * @brief The inner namespace provides specially functionalities relates to
     * physical behaviours.
     */
    namespace physic
    {
        
        /** @brief Collision callbacks for physical solid border. */
        void onLeftRightSolidBorderCollision(Entity &border, Entity &other);
        void onTopBottomSolidBorderCollision(Entity &border, Entity &other);
        
        /** @brief Collision callbacks for simulating actual entity collision. */
        void onEntityCollision(Entity &self, Entity &other);

        /** @brief Collision callbacks for stoping. */
        void onStopCollision(Entity &self, Entity &other);
        
        /** @brief empty Collision Callback. */
        void emptyOnCollision(Entity &self, Entity &other);

    } // physic


} // util

} // AGE


#endif
