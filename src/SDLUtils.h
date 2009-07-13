#ifndef SDL_UTILS_H
#define SDL_UTILS_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
//#include <SDL/SDL_mixer.h>
#include <string>
#include <fstream>
//#include "Globals.h"

//#include <windows.h>

/*
[A][  B  ][C]
[D][BLOCK][F]
[G][  H  ][i]
*/
//const int NO_COLLISION = 0;
const int ZONE_A = 1;
const int ZONE_B = 2;
const int ZONE_C = 3;
const int ZONE_D = 4;
const int ZONE_E = 5;
const int ZONE_F = 6;
const int ZONE_G = 7;
const int ZONE_H = 8;
const int ZONE_I = 9;

SDL_Surface *image_load(std::string filename);
SDL_Surface *image_load(std::string filename, int red, int green, int blue);
void apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *destination);
void apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip);
bool check_collision(SDL_Rect A, SDL_Rect B);
int finde_zone(SDL_Rect A, SDL_Rect B);

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

#endif
