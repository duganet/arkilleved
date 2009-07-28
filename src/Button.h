/*
 *      Button.h
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

#ifndef BUTTON_H
#define BUTTON_H

#include "SDLUtils.h"
#include "Texture.h"

enum
{
    CLIP_MOUSEOVER,
    CLIP_MOUSEOUT,
    CLIP_MOUSEDOWN,
    CLIP_MOUSEUP
};

class Button
{
public:
    Button(int x, int y, std::string filename);
    Button(int x, int y, Texture* texture);
    ~Button();
    void handle_events(SDL_Event &event,void(callback)(void));
    void show();
private:
    SDL_Rect box;
    //SDL_Rect clips[2];
    //SDL_Rect clip;
    SDL_Surface *buttonSheet;
    Texture *texture;
};

#endif
