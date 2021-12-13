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
#include <time.h>

#define AGE_DEFAULT_FPS  2
#define AGE_ENHANCED_FPS 60

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
    Timer(int fps): _first {false}, _duration {1}, 
                    _frameRate {static_cast<float>(fps)}, 
                    _averageFrameRate {static_cast<float>(fps)} 
    {}
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

    /** 
     * @brief Returns the time elapsed between now and the previous frame. 
     * @return The time elapsed in seconds.
     */
    float elapse()
    {
        if (!_first) {
            return 0;
        }

        auto elapse = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - _prev);
        return elapse.count() / 1000.0f;
    }

    /** @brief set the time stamp where the FPS starts to calculate */
    void start() 
    { 
        _stamp1 = clock();
    }

    /** @brief set the time stamp where the FPS stops to calculate */
    void end() 
    { 
        _stamp2 = clock();
        _deltaStamp += _stamp2 - _stamp1;
        ++_frameCnt;

        // calculate FPS once delta time exceeds 1 second
        if ( ((_deltaStamp / (double)CLOCKS_PER_SEC) * 1000.0f) > 1000.0f ) {
            _frameRate = (double)_frameCnt * 0.5f + _frameRate * 0.5f;
            _frameCnt = 0;
            _deltaStamp -= CLOCKS_PER_SEC;
            _averageFrameRate = 1000.0f / (_frameRate == 0 ? 0.001 : _frameRate);
        }
    }

    /** @brief Returns the FPS. */
    double getFPS() { return _averageFrameRate; }

private:
    bool _first;
    // duration between each frame
    std::chrono::duration<double, std::ratio<1, FPS>> _duration;
    // time point on the last frame
    std::chrono::time_point<std::chrono::steady_clock, decltype(_duration)> _prev;
    
    // section to stores the FPS
    clock_t _stamp1, _stamp2;
    clock_t _deltaStamp = 0;
    std::size_t _frameCnt = 0;
    double _frameRate;
    double _averageFrameRate;
};

} // AGE

#endif
