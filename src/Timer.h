/*
 *      Timer.h
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
