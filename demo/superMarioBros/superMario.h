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
        
        playerObj = std::make_shared<NonCollidable>( std::make_shared<RectObject>(Point<float> {4, 4}, 1, 1, "#") );
        bwin.addObject( playerObj );

        /* ASCIIObject */
        // playerObj = std::make_shared<NonCollidable>( std::make_shared<ASCIIObject>(Point<float> {4, 4}, '#') );
        // bwin.addObject( playerObj );
    }

    void onEachFrame(int input) override
    {
        RectObject &player = static_cast<RectObject &>((*playerObj).getObject());
        switch (input) {
            case 'a':
                player.getPos1().getX() -= 1;
                player.getPos2().getX() -= 1;
                break;
            case 'w':
                player.getPos1().getY() -= 1;
                player.getPos2().getY() -= 1;
                break;
            case 's':
                player.getPos1().getY() += 1;
                player.getPos2().getY() += 1;
                break;
            case 'd':
                player.getPos1().getX() += 1;
                player.getPos2().getX() += 1;
                break;
            default:
                break;
        }
    }
private:
    std::shared_ptr<NonCollidable> playerObj;
};

} // AGE

#endif
