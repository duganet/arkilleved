//Timer.h
#ifndef TIMER_H
#define TIMER_H

#include <SDL/SDL.h>

class Timer
{
public:
    Timer();
    void Start();
    void Stop();
    void Pause();
    void UnPause();
    int  Get_Ticks();
    bool Is_Started();
    bool Is_Paused();
private:
    int startTicks;
    int pauseTicks;
    bool started;
    bool paused;
};

#endif
