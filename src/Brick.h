/*
 *      Brick.h
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

#ifndef BRICK_H
#define BRICK_H
#include "SDLUtils.h"
#include "Texture.h"
#include <vector>
#include "GLFT_Font.h"

enum BrickType
{
    BRICK = 101,
    BRICK_STRONG,
    BRICK_BETON
};

class Brick
{
public:
    static std::vector<Brick*> brickList;
    Brick(int type);
    Brick(int type, int x, int y);
    void set_up(int x, int y);
    ~Brick();
    void handle_events(SDL_Event &event);
    void show(SDL_Surface *screen, GLFT_Font *font);
    SDL_Rect get_rect();
    int get_type();
    int get_id();
    void set_id(int i);
    bool get_drag()
    {return drag;}
private:
    SDL_Rect box;
    SDL_Rect prev_box;
    SDL_Surface *sprite;
    Texture texture;
    SDL_Surface *coord;
    //Texture *coord_tex;
    int id;
    bool drag;
    int type;
};

#endif
