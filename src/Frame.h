//Frame.h
#ifndef FRAME_H
#define FRAME_H
#include "SDLUtils.h"
#include "Constants.h"
#include "Brick.h"
#include "Button.h"
#include "Timer.h"
class Frame
{
public:
    Frame();
    ~Frame();
    bool init();
    bool load_files();
    bool main_loop();
    void exit();
    static SDL_Surface *brickStrong_sprite;
    static SDL_Surface *brick_sprite;
    static SDL_Surface *brickBeton_sprite;
private:
    SDL_Surface *screen;
    SDL_Surface *sprite_btnSave;
    SDL_Surface *sprite_btnLoad;
    SDL_Surface *bg;
    SDL_Event event;
    TTF_Font *font;
    bool quit;
};

#endif
