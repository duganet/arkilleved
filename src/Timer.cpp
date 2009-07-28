/*
 *      Timer.cpp
 *      
 *      Copyright 2009 PlugHead Games <plughead@mail.ru>
 *      Copyright 2009 DUGA Project <dev@duganet.ru>
 *      
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *      
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *      
 *      You should have received a copy of the GNU General Public License
 *      along with this program; if not, write to the Free Software
 *      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *      MA 02110-1301, USA.
 */

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
