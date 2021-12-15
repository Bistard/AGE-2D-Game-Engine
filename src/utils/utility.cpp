#include "utility.h"

#include "../model/entity/entity.h"
#include "../model/registry/registry.h"
#include "../model/component/velocity.h"
#include "../model/component/global/border.h"
#include "../model/component/position.h"
#include "../model/component/boundingBox.h"
#include "../model/component/collidable.h"

namespace AGE
{

namespace utils
{

namespace window
{

void setBorderView(Registry &registry, bool visible, int top, int bottom, int left, int right, int corner)
{
    if (registry.hasGlobal<CBorderView>() == false) {
        registry.emplaceGlobal<CBorderView>(visible, top, bottom, left, right, corner);
    } else {
        // if already exists, we only modify the visibility of the border view.
        registry.queryGlobal<CBorderView>().visible = visible;
    }
}


void setSolidBorder(Registry &registry, SIZE winWidth, SIZE winHeight, bool top, bool bottom, bool left, bool right)
{
    // if not exist, we create a new one
    CSolidBorder &border = registry.hasGlobal<CSolidBorder>() == true ? registry.queryGlobal<CSolidBorder>() : registry.emplaceGlobal<CSolidBorder>();

    // If the borderView is displaying, we move the bounding box of the border
    // inside by one more pixel.
    bool visible = false;
    if (registry.hasGlobal<CBorderView>()) {
        visible = registry.queryGlobal<CBorderView>().visible;
    }
    
    // top solid border
    Entity *topEntity = border.top;
    if (top && !topEntity) {
        // we construct a new top border
        topEntity = &registry.create();
        CPosition &topPosition = registry.emplace<CPosition>(*topEntity, 0, visible ? -1 : -2, 0);
        CRectBox &topBox = registry.emplace<CRectBox>(*topEntity, topPosition, winWidth, 1);
        registry.emplace<CCollidable>(*topEntity, topBox);
    } else if (!top && topEntity) {
        // we destroy the existed one
        registry.destroy(*topEntity);
        topEntity = nullptr;
    }
    
    // bottom solid border
    Entity *bottomEntity = border.bottom;
    if (bottom && !bottomEntity) {
        bottomEntity = &registry.create();
        CPosition &bottomPosition = registry.emplace<CPosition>(*bottomEntity, 0, visible ? winHeight - 1 : winHeight, 0);
        CRectBox &bottomBox = registry.emplace<CRectBox>(*bottomEntity, bottomPosition, winWidth, 1);
        registry.emplace<CCollidable>(*bottomEntity, bottomBox);
    } else if (!bottom && bottomEntity) {
        registry.destroy(*bottomEntity);
        bottomEntity = nullptr;
    }

    // left solid border
    Entity *leftEntity = border.left;
    if (left && !leftEntity) {
        leftEntity = &registry.create();
        CPosition &leftPosition = registry.emplace<CPosition>(*leftEntity, visible ? 0 : -1, 0, 0);
        CRectBox &leftBox = registry.emplace<CRectBox>(*leftEntity, leftPosition, 1, winHeight);
        registry.emplace<CCollidable>(*leftEntity, leftBox);
    } else if (!left && leftEntity) {
        registry.destroy(*leftEntity);
        leftEntity = nullptr;
    }

    // right solid border
    Entity *rightEntity = border.right;
    if (right && !rightEntity) {
        rightEntity = &registry.create();
        CPosition &rightPosition = registry.emplace<CPosition>(*rightEntity, visible ? winWidth - 1 : winWidth, 0, 0);
        CRectBox &rightBox = registry.emplace<CRectBox>(*rightEntity, rightPosition, 1, winHeight);
        registry.emplace<CCollidable>(*rightEntity, rightBox);
    } else if (!right && rightEntity) {
        registry.destroy(*rightEntity);
        rightEntity = nullptr;
    }

    // stores them into `CSolidBorder`
    border.top = topEntity;
    border.bottom = bottomEntity;
    border.left = leftEntity;
    border.right = rightEntity;
}

void setSolidBorderCollisionResponse(Registry &registry, bool enable)
{
    try {
        CSolidBorder &border = registry.queryGlobal<CSolidBorder>();

        // if any borders exists, we set the corresponding type of onCollision 
        // callbacks.

        if (border.top) {
            CCollidable &top = registry.get<CCollidable>(*border.top);
            top.onCollision = enable ? physic::onTopBottomSolidBorderCollision : physic::emptyOnCollision;
        }

        if (border.bottom) {
            CCollidable &bottom = registry.get<CCollidable>(*border.bottom);
            bottom.onCollision = enable ? physic::onTopBottomSolidBorderCollision : physic::emptyOnCollision;
        }

        if (border.left) {
            CCollidable &left = registry.get<CCollidable>(*border.left);
            left.onCollision = enable ? physic::onLeftRightSolidBorderCollision : physic::emptyOnCollision;
        }

        if (border.right) {
            CCollidable &right = registry.get<CCollidable>(*border.right);
            right.onCollision = enable ? physic::onLeftRightSolidBorderCollision : physic::emptyOnCollision;
        }

    } catch (...) {
        // Reaches here means no `CSolidBorder` exists or missing any other 
        // `CCollidable` components. We simply ignore the exceptions.
    }
}

}


namespace physic
{

void onLeftRightSolidBorderCollision(Entity &border, Entity &other)
{
    if (other.getRegistry().has<CVelocity>(other) == true) {
        CVelocity &velocity = other.getRegistry().get<CVelocity>(other);
        velocity.val.getX() *= -1;
    }
}

void onTopBottomSolidBorderCollision(Entity &border, Entity &other)
{
    if (other.getRegistry().has<CVelocity>(other) == true) {
        CVelocity &velocity = other.getRegistry().get<CVelocity>(other);
        velocity.val.getY() *= -1;
    }
}

void emptyOnCollision(Entity &border, Entity &other)
{
    // empty function body.
}

} // physic


} // util

} // AGE
