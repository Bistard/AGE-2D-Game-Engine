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
        
        playerObj = std::make_shared<NonCollidable>( std::make_shared<RectObject>(vec2d<float> {4, 4}, 1, 1, "#") );
        bwin.addNonCollidable( playerObj );

        obj1 =  std::make_shared<Movable>( std::make_shared<NonCollidable>( std::make_shared<RectObject>(vec2d<float> {20, 5}, 5, 5, "O") ) );
        bwin.addNonCollidable( obj1 );
        obj1->setAltitude(5);
        obj1->setVelocity(vec2d<float> {0.12f, 0.0f});
        
        /* ASCIIObject */
        // playerObj = std::make_shared<NonCollidable>( std::make_shared<ASCIIObject>(vec2d<float> {4, 4}, '#') );
        // bwin.addObject( playerObj );
    }

    void onEachFrame(int input) override
    {
        RectObject &player = static_cast<RectObject &>((*playerObj).getObject());
        switch (input) {
            case 'a':
                player.getPosition().getX() -= 1;
                break;
            case 'w':
                player.getPosition().getY() -= 1;
                break;
            case 's':
                player.getPosition().getY() += 1;
                break;
            case 'd':
                player.getPosition().getX() += 1;
                break;
            default:
                break;
        }
    }
private:
    std::shared_ptr<NonCollidable> playerObj;
    std::shared_ptr<Movable> obj1;
};

} // AGE

#endif
