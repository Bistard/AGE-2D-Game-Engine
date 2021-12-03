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
        this->getWindow().drawViews();
        
        // construct my Playable Object during initialization
        std::unique_ptr<NonCollidable> MyPlayableRect = std::make_unique<NonCollidable>( std::make_unique<RectObject>(Point<float> {4, 4}, Point<float> {10, 10}, "#") );
        Object &refToPlayer = bwin.addObject( std::move(MyPlayableRect) );
    }

    void onEachFrame(int input) override
    {
        switch (input) {
        case 'a':
            break;
        case 'w':
            break;
        case 's':
            break;
        case 'd':
            break;
        default:
            break;
        }
    }
private:
    
};

} // AGE

#endif
