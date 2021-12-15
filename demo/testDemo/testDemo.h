/**
 * @file testDemo.h
 * @author Sihan Li (lshh1015813038@gmail.com)
 * @brief The client class to demonstrate the power of the AGE engine.
 * @version 0.1
 * @date 2021-12-13
 */

#ifndef __TEST_DEMO__
#define __TEST_DEMO__

#include "../../src/ageEngine.h"

namespace AGE
{

template<std::intmax_t FPS = AGE_DEFAULT_FPS>
class TestDemo : public AgeEngine<FPS>
{
public:
    TestDemo(int fps, SIZE width, SIZE height): AgeEngine<FPS> {fps, width, height} {}
    ~TestDemo() {}
private:
    void init() override
    {
        __test_controller();
        __test_renderer_system();
        __test_motion_system();
        __test_collision_system();
        __test_despawn_system();
    }

    void onEachFrame(int input) override
    {
        GameWindow &win = static_cast<GameWindow &>(this->getWindow());
        BoardWindow &bwin = win.getBoardWindow();
        Registry &registry = bwin.getScene().getRegistry();

        /** @brief testing - Text rendering (rendering FPS) */
        textFPS->text = std::to_string(this->getFPS());

        /** @brief testing - Text rendering (count alive entities) */
        textEntityCnt->text = "Entity Count: " + std::to_string(registry.size());

        CPosition &position = registry.get<CPosition>(*player);

        switch (input)
        {
            case 'a':
                position.val.getX() -= 1;
                lastMovement = 'a';
                break;
            case 'w':
                position.val.getY() -= 1;
                lastMovement = 'w';
                break;
            case 's':
                position.val.getY() += 1;
                lastMovement = 's';
                break;
            case 'd':
                position.val.getX() += 1;
                lastMovement = 'd';
                break;
            case 32:
                {
                    // shooting bullet
                    Entity &bullet = registry.create();
                    CRectangle &texture1 = registry.emplace<CRectangle>(bullet, 1, 1, "+");
                    CPosition &position1 = registry.emplace<CPosition>(bullet, position.val.X(), position.val.Y(), 1);
                    registry.emplace<CRenderer>(bullet, texture1, position1);

                    switch (lastMovement)
                    {
                    case 'a':
                        registry.emplace<CVelocity>(bullet, -1.0f, 0.0f);
                        break;
                    case 'w':
                        registry.emplace<CVelocity>(bullet, 0.0f, -1.0f);
                        break;
                    case 's':
                        registry.emplace<CVelocity>(bullet, 0.0f, 1.0f);
                        break;
                    case 'd':
                        registry.emplace<CVelocity>(bullet, 1.0f, 0.0f);
                        break;
                    default:
                        break;
                    }

                    registry.emplace<CDespawn>(bullet, position1);
                    break;
                }
            case 'b':
                {
                    // shooting bullet
                    Entity &bullet = registry.create();
                    CRectangle &texture1 = registry.emplace<CRectangle>(bullet, 2, 2, "+");
                    CPosition &position1 = registry.emplace<CPosition>(bullet, position.val.X(), position.val.Y(), 1);
                    registry.emplace<CRenderer>(bullet, texture1, position1);

                    switch (lastMovement)
                    {
                    case 'a':
                        registry.emplace<CVelocity>(bullet, -1.0f, 0.0f);
                        break;
                    case 'w':
                        registry.emplace<CVelocity>(bullet, 0.0f, -1.0f);
                        break;
                    case 's':
                        registry.emplace<CVelocity>(bullet, 0.0f, 1.0f);
                        break;
                    case 'd':
                        registry.emplace<CVelocity>(bullet, 1.0f, 0.0f);
                        break;
                    default:
                        break;
                    }

                    registry.emplace<CDespawn>(bullet, position1);
                    break;
                }
            case 'c':

                {
                    // shooting bullet that collides
                    Entity &bullet = registry.create();
                    CRectangle &texture1 = registry.emplace<CRectangle>(bullet, 1, 1, "@");
                    CPosition &position1 = registry.emplace<CPosition>(bullet, position.val.X(), position.val.Y(), 1);
                    registry.emplace<CRenderer>(bullet, texture1, position1);

                    switch (lastMovement)
                    {
                    case 'a':
                        registry.emplace<CVelocity>(bullet, utils::randFloatNum(-1, 1), utils::randFloatNum(-1, 1));
                        break;
                    case 'w':
                        registry.emplace<CVelocity>(bullet, utils::randFloatNum(-1, 1), utils::randFloatNum(-1, 1));
                        break;
                    case 's':
                        registry.emplace<CVelocity>(bullet, utils::randFloatNum(-1, 1), utils::randFloatNum(-1, 1));
                        break;
                    case 'd':
                        registry.emplace<CVelocity>(bullet, utils::randFloatNum(-1, 1), utils::randFloatNum(-1, 1));
                        break;
                    default:
                        break;
                    }

                    registry.emplace<CDespawn>(bullet, position1);
                    CRectBox &box = registry.emplace<CRectBox>(bullet, position1, 1, 1);
                    registry.emplace<CCollidable>(bullet, box);
                    break;
                }

                break;
            default:
                break;
        }
    }
private:
    CText *textFPS, *textEntityCnt;
    Entity *player;
    int lastMovement = 'd';

private:

    void __test_controller()
    {
        GameWindow &win = static_cast<GameWindow &>(this->getWindow());
        BoardWindow &bwin = win.getBoardWindow();
        Registry &registry = bwin.getScene().getRegistry();

        player = &registry.create();
        CASCII &texture = registry.emplace<CASCII>(*player, "C");
        CPosition &position = registry.emplace<CPosition>(*player, bwin.getWidth() / 2, bwin.getHeight() / 2, 0);
        registry.emplace<CRenderer>(*player, texture, position);
    }

    void __test_renderer_system()
    {
        GameWindow &win = static_cast<GameWindow &>(this->getWindow());

        /** @brief BoardWindow */

        BoardWindow &bwin = win.getBoardWindow();

        Registry &registry1 = bwin.getScene().getRegistry();

        utils::window::setBorderView(registry1, true, '-', '-', '|', '|', '+');

        /** @brief testing - ascii rendering */
        Entity &e1 = registry1.create();

        CASCII &texture1 = registry1.emplace<CASCII>(e1, "X");
        CPosition &position1 = registry1.emplace<CPosition>(e1, 1, 1, 0);
        registry1.emplace<CRenderer>(e1, texture1, position1);

        /** @brief testing - rectangle rendering */
        Entity &e2 = registry1.create();

        CRectangle &texture2 = registry1.emplace<CRectangle>(e2, 3, 3, "#");
        CPosition &position2 = registry1.emplace<CPosition>(e2, 3, 1, 0);
        registry1.emplace<CRenderer>(e2, texture2, position2);

        /** @brief testing - Bitmap rendering */
        Entity &e3 = registry1.create();

        CBitmap &texture3 = registry1.emplace<CBitmap>(e3, std::vector<triple> { {0, 1, "a"}, {1, 0, "b"}, {1, 2, "c"}, {2, 1, "d"}, {1, 1, "e"} } );
        CPosition &position3 = registry1.emplace<CPosition>(e3, 7, 1, 0);
        registry1.emplace<CRenderer>(e3, texture3, position3);

        /** @brief StatusWindow */

        StatusWindow &swin = win.getStatusWindow();
        Registry &registry2 = swin.getScene().getRegistry();

        /** @brief testing - Text rendering (rendering FPS) */
        Entity &e4 = registry2.create();

        textFPS = &registry2.emplace<CText>(e4, "FPS: " + std::to_string(this->getFPS()) );
        CPosition &position4 = registry2.emplace<CPosition>(e4, 0.0f, 0.0f, 0);
        registry2.emplace<CRenderer>(e4, *textFPS, position4);

        /** @brief testing - Text rendering (count alive entities) */
        Entity &e5 = registry2.create();
        textEntityCnt = &registry2.emplace<CText>(e5, "Entity Count: " + std::to_string(registry2.size()) );
        CPosition &position5 = registry2.emplace<CPosition>(e5, 0.0f, 1.0f, 0);
        registry2.emplace<CRenderer>(e5, *textEntityCnt, position5);
    }

    void __test_motion_system()
    {
        GameWindow &win = static_cast<GameWindow &>(this->getWindow());
        BoardWindow &bwin = win.getBoardWindow();
        Registry &registry = bwin.getScene().getRegistry();

        /** @brief testing - constant velocity */
        Entity &e1 = registry.create();

        CBitmap &texture1 = registry.emplace<CBitmap>(e1, std::vector<triple> { {0, 0, "Y"}, {0, 1, "|"}, {0, 2, "T"} } );
        CPosition &position1 = registry.emplace<CPosition>(e1, 12, 1, 1);
        registry.emplace<CRenderer>(e1, texture1, position1);
        registry.emplace<CVelocity>(e1, 0.0f, 0.5f);

        /** @brief testing - gravity */
        Entity &e2 = registry.create();

        CBitmap &texture2 = registry.emplace<CBitmap>(e2, std::vector<triple> { {0, 0, "|"}, {0, 1, "|"}, {0, 2, "O"} } );
        CPosition &position2 = registry.emplace<CPosition>(e2, 15, 1, 1);
        registry.emplace<CRenderer>(e2, texture2, position2);
        registry.emplace<CVelocity>(e2, 0.0f, 0.0f);
        registry.emplace<CGravity>(e2, 0.0f, 0.01f);

        /** @brief testing - different movement */

    }

    void __test_collision_system()
    {
        GameWindow &win = static_cast<GameWindow &>(this->getWindow());
        BoardWindow &bwin = win.getBoardWindow();
        Registry &registry = bwin.getScene().getRegistry();

        utils::window::setSolidBorder(registry, bwin.getWidth(), bwin.getHeight(), true, true, true, true);
        utils::window::setSolidBorderCollisionResponse(registry, true);

        Entity &e0 = registry.create();

        CBitmap &texture0 = registry.emplace<CBitmap>(e0, std::vector<triple> { {0, 0, "|"}, {0, 1, "|"}, {0, 2, "O"} } );
        CPosition &position0 = registry.emplace<CPosition>(e0, 18, 1, 1);
        CRectBox &box0 = registry.emplace<CRectBox>(e0, position0, 1, 3);
        registry.emplace<CRenderer>(e0, texture0, position0);
        registry.emplace<CVelocity>(e0, 0.0f, 0.0f);
        registry.emplace<CGravity>(e0, 0.0f, 0.1f);
        registry.emplace<CCollidable>(e0, box0);

        Entity &e00 = registry.create();

        CBitmap &texture00 = registry.emplace<CBitmap>(e00, std::vector<triple> { {0, 0, "|"}, {0, 1, "|"}, {0, 2, "O"} } );
        CPosition &position00 = registry.emplace<CPosition>(e00, 21, 30, 1);
        CRectBox &box00 = registry.emplace<CRectBox>(e00, position00, 1, 3);
        registry.emplace<CRenderer>(e00, texture00, position00);
        registry.emplace<CVelocity>(e00, 0.0f, 0.0f);
        registry.emplace<CGravity>(e00, 0.0f, 0.1f);
        registry.emplace<CCollidable>(e00, box00, [](Entity &self, Entity &other) {
            if (self.getRegistry().has<CVelocity>(self) == true) {
                CVelocity &velocity = self.getRegistry().get<CVelocity>(self);
                velocity.val.getX() = 0;
                velocity.val.getY() = 0;
            }
        });

        Entity &e1 = registry.create();
        CASCII &texture1 = registry.emplace<CASCII>(e1, "0");
        CPosition &position1 = registry.emplace<CPosition>(e1, 50.0f, 10.0f, 10);
        CRectBox &box1 = registry.emplace<CRectBox>(e1, position1, 1, 1);
        registry.emplace<CRenderer>(e1, texture1, position1);
        registry.emplace<CVelocity>(e1, 0.5f, 0.5f);
        registry.emplace<CCollidable>(e1, box1);

        Entity &e2 = registry.create();
        CBitmap &texture2 = registry.emplace<CBitmap>(e2, std::vector<triple> { {0, 0, "X"} } );
        CPosition &position2 = registry.emplace<CPosition>(e2, 60.0f, 10.0f, 10);
        CRectBox &box2 = registry.emplace<CRectBox>(e2, position2, 1, 1);
        registry.emplace<CRenderer>(e2, texture2, position2);
        registry.emplace<CVelocity>(e2, -0.5f, -0.5f);
        registry.emplace<CCollidable>(e2, box2);

        Entity &e3 = registry.create();
        CBitmap &texture3 = registry.emplace<CBitmap>(e3, std::vector<triple> { {0, 0, "1"}, {1, 1, "1"} } );
        CPosition &position3 = registry.emplace<CPosition>(e3, 40.0f, 5.0f, 10);
        CRectBox &box3 = registry.emplace<CRectBox>(e3, position3, 2, 2);
        registry.emplace<CRenderer>(e3, texture3, position3);
        registry.emplace<CVelocity>(e3, -0.5f, 0.0f);
        registry.emplace<CCollidable>(e3, box3, utils::physic::onEntityCollision);

        Entity &e4 = registry.create();
        CRectangle &texture4 = registry.emplace<CRectangle>(e4, 4, 4, "#");
        CPosition &position4 = registry.emplace<CPosition>(e4, 20.0f, 5.0f, 8);
        CRectBox &box4 = registry.emplace<CRectBox>(e4, position4, 4, 4);
        registry.emplace<CRenderer>(e4, texture4, position4);
        registry.emplace<CVelocity>(e4, 0.5f, 0.0f);
        registry.emplace<CCollidable>(e4, box4, utils::physic::onEntityCollision);
    }

    void __test_despawn_system()
    {
        // GameWindow &win = static_cast<GameWindow &>(this->getWindow());
        // BoardWindow &bwin = win.getBoardWindow();
        // Registry &registry = bwin.getScene().getRegistry();

        // Entity &e1 = registry.create();
        // CRectangle &texture1 = registry.emplace<CRectangle>(e1, 4, 4, "+");
        // CPosition &position1 = registry.emplace<CPosition>(e1, 80.0f, 10.0f, 1);
        // registry.emplace<CRenderer>(e1, texture1, position1);
        // registry.emplace<CVelocity>(e1, -2.0f, 0.0f);
        // registry.emplace<CDespawn>(e1, position1);

        // Entity &e2 = registry.create();
        // CRectangle &texture2 = registry.emplace<CRectangle>(e2, 4, 4, "-");
        // CPosition &position2 = registry.emplace<CPosition>(e2, 30, 1, 1);
        // registry.emplace<CRenderer>(e2, texture2, position2);
        // registry.emplace<CVelocity>(e2, 0.0f, 2.0f);
        // registry.emplace<CDespawn>(e2, position2);
    }
};

} // AGE

#endif
