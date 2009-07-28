/*
 *      SDLUtils.h
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

#ifndef SDL_UTILS_H
#define SDL_UTILS_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_opengl.h>
//#include <SDL/SDL_mixer.h>
#include <string>
#include <fstream>
#include <vector>
//#include "Globals.h"

SDL_Surface *image_load(std::string filename);
SDL_Surface *image_load(std::string filename, int red, int green, int blue);
void apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *destination);
void apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip);
bool check_collision(SDL_Rect A, SDL_Rect B);


struct Point
{
    int x;
    int y;
};

void log(std::string message);

enum GameStates
{
    STATE_NULL,
    STATE_INTRO,
    STATE_TITLE,
    STATE_LEVEL_1,
    STATE_LEVEL_2,
    STATE_GAMEOVER,
    STATE_EXIT
};

enum Textures
{
    BRICK_TEX,
    BRICK_STRONG_TEX,
    BRICK_BETON_TEX,
    BTN_SAVE_TEX,
    BTN_LOAD_TEX,
    BG_TEX
};

#endif
