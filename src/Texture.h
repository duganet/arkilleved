/*
 *      Texture.h
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

#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include "Constants.h"
#include <string>

class Texture
{
public:
    ~Texture();
    bool load_from_file(std::string filename);
    bool load_from_file(std::string filename, int r, int g, int b);
    bool load_from_surface(SDL_Surface* source);
    void show(int x, int y);
    GLuint get_texture(){return texture;}
    int get_width(){return surface_w;}
    int get_height(){return surface_h;}
    int w,h;
private:
    GLuint texture;
    GLenum eFormat;

    int surface_w, surface_h;
    double wdt, hgt;
};


#endif
