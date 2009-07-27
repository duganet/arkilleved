//Frame.h
#ifndef FRAME_H
#define FRAME_H

#include "SDLUtils.h"
#include "Constants.h"
#include "Brick.h"
#include "Button.h"
#include "Timer.h"
#include "Texture.h"
#include <vector>

class Frame
{
public:
    Frame();
    ~Frame();
    bool init();
    bool initGL();
    bool load_files();
    bool main_loop();
    void exit();
private:
    SDL_Surface *screen;

    SDL_Event event;
    TTF_Font *font;
    bool quit;
};

#endif
