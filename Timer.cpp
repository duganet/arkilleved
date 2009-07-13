//Timer.cpp
#include "Timer.h"

Timer::Timer()
{
    startTicks = 0;
    pauseTicks = 0;
    started = false;
    paused = false;
}

void Timer::Start()
{
    started = true;
    paused = false;
    startTicks = SDL_GetTicks();
}

void Timer::Stop()
{
    started = false;
    paused = false;
}

void Timer::Pause()
{
    if ((started == true) && (paused == false))
    {
        paused = true;
        pauseTicks = SDL_GetTicks() - startTicks;
    }
}

void Timer::UnPause()
{
    if((started == true) && (paused == true))
    {
        paused = false;
        startTicks = SDL_GetTicks() - pauseTicks;
        pauseTicks = 0;
    }
}

bool Timer::Is_Started()
{
    return started;
}

bool Timer::Is_Paused()
{
    return paused;
}

int Timer::Get_Ticks()
{
    if(started == true)
    {
        if(paused == true)
        {
            return pauseTicks;
        }
        else
        {
            return SDL_GetTicks() - startTicks;
        }
    }
    return 0;
}
