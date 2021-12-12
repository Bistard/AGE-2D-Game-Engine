/**
 * @file superMario.h
 * @author Sihan Li (lshh1015813038@gmail.com)
 * @brief The client class to implement Super Mario Bros World 1-1 using AGE 
 *   engine.
 * @version 0.1
 * @date 2021-11-28
 */

#ifndef __SUPER_MARIO_BROS__
#define __SUPER_MARIO_BROS__

#include "../../src/ageEngine.h"

namespace AGE
{

template<std::intmax_t FPS = AGE_DEFAULT_FPS>
class SuperMarioEngine : public AgeEngine<FPS>
{
public:
    SuperMarioEngine(int fps, SIZE width, SIZE height): AgeEngine<FPS> {fps}
    {}
    ~SuperMarioEngine() {}

private:
    void init() override
    {
        GameWindow &win = static_cast<GameWindow &>(this->getWindow());
        BoardWindow &bwin = win.getBoardWindow();
        bwin.setBorder(true, '-', '-', '|', '|', '+');
        
        __test_registry();
        
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
    void __test_registry()
    {
        GameWindow &win = static_cast<GameWindow &>(this->getWindow());
        BoardWindow &bwin = win.getBoardWindow();
        Registry &registry = bwin.getScene().getRegistry();

        /** @brief create our PLAYER entity. */
        Entity &player = registry.create();
        
        CASCII &texture1 = registry.emplace<CASCII>(player, "X");
        CPosition &position1 = registry.emplace<CPosition>(player, 2.3f, 4.5f, 0);

        registry.emplace<CRenderer>(player, texture1, position1);


        /** @brief create our #2 entity. */
        Entity &entity2 = registry.create();
        
        CRectangle &texture2 = registry.emplace<CRectangle>(entity2, 5, 3, "#");
        CPosition &position2 = registry.emplace<CPosition>(entity2, 10.3f, 7.5f, 0);

        registry.emplace<CRenderer>(entity2, texture2, position2);

        /** @brief create our #3 entity. */
        Entity &entity3 = registry.create();
        
        std::vector<triple> bitmap;
        bitmap.emplace_back(0, 1, "a");
        bitmap.emplace_back(1, 0, "b");
        bitmap.emplace_back(1, 2, "c");
        bitmap.emplace_back(2, 1, "d");
        CBitmap &texture3 = registry.emplace<CBitmap>(entity3, bitmap);
        CPosition &position3 = registry.emplace<CPosition>(entity3, 20.7f, 1.5f, 0);

        registry.emplace<CRenderer>(entity3, texture3, position3);
    }

};

} // AGE

#endif
