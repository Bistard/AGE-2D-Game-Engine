/**
 * @file render.h
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

using AltitudeType = uint8_t;

/** 
 * @brief A composite component for rendering usage.
 * - CTexture
 * - CPosition
 */
class CRender : public Component
{
public:
    CRender(Entity &entity, AltitudeType altitude, bool visible, 
            CTexture &texture, CPosition &position
    ) : Component {entity}, altitude {altitude}, visible {visible}, 
        texture {texture}, position {position} 
    {}
    ~CRender() override {}
public:
    /** @brief determine whether to render */
    bool visible;
    /** @brief altitude in the drawing */
    AltitudeType altitude;
    /** @brief texture data for drawing */
    CTexture &texture;
    /** @brief position for drawing */
    CPosition &position;
};

} // AGE

#endif
