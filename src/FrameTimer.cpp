#include "FrameTimer.hpp"

FrameTimer::FrameTimer()
{
    old = std::chrono::steady_clock::now();
}

float FrameTimer::Mark()
{
    auto now = std::chrono::steady_clock::now();
    std::chrono::duration<float> dur;
    dur = now - old;
    old = now;
    return dur.count();
}