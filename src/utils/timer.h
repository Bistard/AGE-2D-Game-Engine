/**
 * @file timer.h
 * @author Sihan Li (lshh1015813038@gmail.com)
 * @brief This is a timer class to control the refresh rate.
 * @version 0.1
 * @date 2021-11-27
 */

#ifndef __AGE_TIMER__
#define __AGE_TIMER__

#include <chrono>
#include <thread>

namespace AGE
{

/**
 * @brief A template timer that using universal clocking (not based on the 
 *   operating system). 
 * The frame rate must be defined in the compile-time.
 */
template<std::intmax_t FPS>
class Timer
{
public:
    Timer(): _first {false}, _duration {1} {}
    ~Timer() = default;
public:
    /**
     * @brief pauses the program based on last call to `tick()`. Does not pause 
     *   on the first call. It can be reseted.
     */
    void tick()
    {   
        if (!_first) {
            _first = true;
            _prev = std::chrono::steady_clock::now();
            return;
        }

        _prev += _duration;
        std::this_thread::sleep_until(_prev);
    }
private:
    bool _first;
    // duration between each frame
    std::chrono::duration<double, std::ratio<1, FPS>> _duration;
    // time point on the last frame
    std::chrono::time_point<std::chrono::steady_clock, decltype(_duration)> _prev;
};

} // AGE

#endif
