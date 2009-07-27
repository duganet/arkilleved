//Texture.h
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
