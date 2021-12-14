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
    TestDemo(int fps, SIZE width, SIZE height): AgeEngine<FPS> {fps} {}
    ~TestDemo() {}
private:
    void init() override
    {
        __test_renderer_system();
        __test_motion_system();
        __test_collision_system();
    }

    void onEachFrame(int input) override
    {
        // RectObject &player = static_cast<RectObject &>((*playerObj).getObject());
        // switch (input) {
        //     case 'a':
        //         player.getPosition().getX() -= 1;
        //         break;
        //     case 'w':
        //         player.getPosition().getY() -= 1;
        //         break;
        //     case 's':
        //         player.getPosition().getY() += 1;
        //         break;
        //     case 'd':
        //         player.getPosition().getX() += 1;
        //         break;
        //     default:
        //         break;
        // }
    }
private:
    void __test_renderer_system()
    {
        GameWindow &win = static_cast<GameWindow &>(this->getWindow());
     
        /** @brief BoardWindow */
     
        BoardWindow &bwin = win.getBoardWindow();
        bwin.setBorderView(true, '-', '-', '|', '|', '+');

        Registry &registry1 = bwin.getScene().getRegistry();

        /** @brief testing - ascii rendering */
        Entity &e1 = registry1.create();
        
        CASCII &texture1 = registry1.emplace<CASCII>(e1, "X");
        CPosition &position1 = registry1.emplace<CPosition>(e1, 2.3f, 4.5f, 0);
        registry1.emplace<CRenderer>(e1, texture1, position1);

        /** @brief testing - rectangle rendering */
        Entity &e2 = registry1.create();
        
        CRectangle &texture2 = registry1.emplace<CRectangle>(e2, 5, 3, "#");
        CPosition &position2 = registry1.emplace<CPosition>(e2, 10.3f, 7.5f, 0);
        registry1.emplace<CRenderer>(e2, texture2, position2);

        /** @brief testing - Bitmap rendering */
        Entity &e3 = registry1.create();
        
        CBitmap &texture3 = registry1.emplace<CBitmap>(e3, std::vector<triple> { {0, 1, "a"}, {1, 0, "b"}, {1, 2, "c"}, {2, 1, "d"} } );
        CPosition &position3 = registry1.emplace<CPosition>(e3, 20.7f, 1.5f, 0);
        registry1.emplace<CRenderer>(e3, texture3, position3);

        /** @brief StatusWindow */

        StatusWindow &swin = win.getStatusWindow();
        Registry &registry2 = swin.getScene().getRegistry();

        /** @brief testing - Text rendering */
        Entity &e4 = registry2.create();

        CText &texture4 = registry2.emplace<CText>(e4, "FPS: " + std::to_string(this->getFPS()) );
        CPosition &position4 = registry2.emplace<CPosition>(e4, 0.0f, 0.0f, 10);
        registry2.emplace<CRenderer>(e4, texture4, position4);
        
    }

    void __test_motion_system()
    {
        GameWindow &win = static_cast<GameWindow &>(this->getWindow());
        BoardWindow &bwin = win.getBoardWindow();
        Registry &registry = bwin.getScene().getRegistry();

        /** @brief testing - constant velocity */
        Entity &e1 = registry.create();
        
        CBitmap &texture1 = registry.emplace<CBitmap>(e1, std::vector<triple> { {0, 0, "-"}, {1, 0, "-"}, {2, 0, ">"} } );
        CPosition &position1 = registry.emplace<CPosition>(e1, 2.3f, 4.5f, 1);
        registry.emplace<CRenderer>(e1, texture1, position1);
        registry.emplace<CVelocity>(e1, 1.0f, 0.0f);

        /** @brief testing - gravity */
        Entity &e2 = registry.create();
        
        CBitmap &texture2 = registry.emplace<CBitmap>(e2, std::vector<triple> { {0, 0, "|"}, {0, 1, "|"}, {0, 2, "O"} } );
        CPosition &position2 = registry.emplace<CPosition>(e2, 40.0f, 20.0f, 1);
        registry.emplace<CRenderer>(e2, texture2, position2);
        registry.emplace<CVelocity>(e2, 0.0f, -3.0f);
        registry.emplace<CGravity>(e2, 0.0f, 0.25f);
    }

    void __test_collision_system()
    {
        GameWindow &win = static_cast<GameWindow &>(this->getWindow());
        BoardWindow &bwin = win.getBoardWindow();
        bwin.setSolidBorder(true, true, true, true);
        
        Registry &registry = bwin.getScene().getRegistry();
        
        Entity &e1 = registry.create();
        CBitmap &texture1 = registry.emplace<CBitmap>(e1, std::vector<triple> { {0, 0, "O"} } );
        CPosition &position1 = registry.emplace<CPosition>(e1, 10.0f, 10.0f, 10);
        CRectBox &box1 = registry.emplace<CRectBox>(e1, position1, 1, 1);
        registry.emplace<CRenderer>(e1, texture1, position1);
        registry.emplace<CVelocity>(e1, 0.25f, 0.25f);
        registry.emplace<CCollidable>(e1, box1, [](Entity &other) {
            // FIXME: Entity should obtain such API's for convinence purpose
            // CVelocity &velocity = registry.get<CVelocity>(e1);
            // velocity.val.getX() *= -1;
            // velocity.val.getY() *= -1;
        });
    }
};

} // AGE

#endif
