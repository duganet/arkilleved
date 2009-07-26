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
