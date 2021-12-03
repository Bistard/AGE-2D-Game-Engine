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
        
        std::unique_ptr<NonCollidable> obj1 = std::make_unique<NonCollidable>( std::make_unique<RectObject>(Point<float> {4, 4}, Point<float> {6, 6}, "#") );
        bwin.addObject( std::move(obj1) );

        std::unique_ptr<NonCollidable> obj2 = std::make_unique<NonCollidable>( std::make_unique<RectObject>(Point<float> {10, 4}, Point<float> {14, 8}, "*") );
        bwin.addObject( std::move(obj2) );

        std::unique_ptr<NonCollidable> obj3 = std::make_unique<NonCollidable>( std::make_unique<RectObject>(Point<float> {30, 10}, Point<float> {40, 14}, "O") );
        bwin.addObject( std::move(obj3) );
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
