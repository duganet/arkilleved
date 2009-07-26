//Brick.h
#ifndef BRICK_H
#define BRICK_H
#include "SDLUtils.h"
#include "Texture.h"
#include <vector>

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
    Brick(SDL_Surface* sprite, int type);
    Brick(SDL_Surface* sprite, int type, int x, int y);
    void set_up(int x, int y);
    ~Brick();
    void handle_events(SDL_Event &event);
    void show(SDL_Surface *screen, TTF_Font *font);
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
