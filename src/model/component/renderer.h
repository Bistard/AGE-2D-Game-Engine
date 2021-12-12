/**
 * @file renderer.h
 * @author Sihan Li (lshh1015813038@gmail.com)
 * @version 0.1
 * @date 2021-12-12
 */

#ifndef __AGE_RENDER_COMPONENT__
#define __AGE_RENDER_COMPONENT__

#include "component.h"
#include "position.h"
#include "texture.h"

namespace AGE
{

/** 
 * @brief A composite component for rendering usage.
 * - CTexture
 * - CPosition
 */
class CRenderer : public Component
{
public:
    CRenderer(Entity &entity, CTexture &texture, CPosition &position, bool visible = true)
     : Component {entity}, texture {texture}, position {position}, visible {visible}
    {}
    ~CRenderer() override {}
public:
    /** @brief texture data for drawing */
    CTexture &texture;
    /** @brief position for drawing */
    CPosition &position;
    /** @brief determine whether to render */
    bool visible;
};

/** @brief Class for comparing between `CRenderer` */
class CRendererCompare
{
public:
    bool operator() (CRenderer *r1, CRenderer *r2)
    {
        return r1->position.altitude >= r2->position.altitude;
    }
};

} // AGE

#endif
