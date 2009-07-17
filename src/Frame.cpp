//Frame.cpp
#include "Frame.h"
#include <fstream>
#include <sstream>

SDL_Surface* Frame::brickStrong_sprite;
SDL_Surface* Frame::brick_sprite;
SDL_Surface* Frame::brickBeton_sprite;

Frame::Frame()
{
    screen = NULL;
    quit = false;
    brickStrong_sprite = NULL;
    brick_sprite = NULL;
    sprite_btnSave = NULL;
    sprite_btnLoad = NULL;
    bg = NULL;
    font = NULL;
}

Frame::~Frame()
{
    exit();
}

bool Frame::init()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        log("ERROR: init failed");
        return false;
    }
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
    if(screen == NULL)
    {
        log("ERROR: set video mode faled");
        return false;
    }
    SDL_WM_SetCaption("Arkilloid Level Editor", NULL);

    if(TTF_Init() == -1)
    {
        log("ERROR: TTF not init");
        return false;
    }
    return true;
}

bool Frame::load_files()
{
    std::string imagedir;
    std::string img_filename;
    #ifdef WIN32
    imagedir = "images";
    #else
    imagedir = "../share/arkilloid-leveledit/images";
    #endif
    log(pkgdatadir);
    img_filename = imagedir + "/brick.png";
    brick_sprite = image_load(img_filename, 0xFF,0,0xFF);
    if(brick_sprite == NULL)
    {
        log(img_filename + " not found");
        return false;
    }

    img_filename = imagedir + "/brick_strong.png";
    brickStrong_sprite = image_load(img_filename, 0xFF,0,0xFF);
    if(brickStrong_sprite == NULL)
    {
        log(img_filename + " not found");
        return false;
    }

    img_filename = imagedir + "/brick_beton.png";
    brickBeton_sprite = image_load(img_filename, 0xFF,0,0xFF);
    if(brickBeton_sprite == NULL)
    {
        log(img_filename + " not found");
        return false;
    }
    img_filename = imagedir + "/button_save.png";
    sprite_btnSave = image_load(img_filename, 0xFF,0,0xFF);
    if(sprite_btnSave == NULL)
    {
        log(img_filename + " not found");
        return false;
    }
    img_filename = imagedir + "/button_open.png";
    sprite_btnLoad = image_load(img_filename, 0xFF,0,0xFF);
    if(sprite_btnLoad == NULL)
    {
        log(img_filename + " not found");
        return false;
    }
    img_filename = imagedir + "/bg.bmp";
    bg = image_load(img_filename);

    font = TTF_OpenFont("fonts/aerial.ttf", 10);
    if(font == NULL)
    {
        log("ERROR: font not load");
        return false;
    }
    return true;
}


void buttonBrick_click()
{
    Brick *brick = new Brick(Frame::brick_sprite, BRICK);
    Brick::brickList.push_back(brick);
}

void buttonStrongBrick_click()
{
    Brick *brick = new Brick(Frame::brickStrong_sprite, BRICK_STRONG);
    Brick::brickList.push_back(brick);
}

void buttonBetonBrick_click()
{
    Brick *brick = new Brick(Frame::brickBeton_sprite, BRICK_BETON);
    Brick::brickList.push_back(brick);
}

void buttonSave_click()
{
    std::ofstream f("level.map");

    f << Brick::brickList.size() << std::endl;
    for(unsigned int i = 0; i < Brick::brickList.size();i++)
    {
        f << Brick::brickList[i]->get_type() << " "
          << Brick::brickList[i]->get_rect().x << " "
          << Brick::brickList[i]->get_rect().y << std::endl;
    }

    f.flush();
}

void buttonLoad_click()
{
    FILE *FileHandle = fopen("level.map", "r");

    int brickCount = 0;
    int brickType = 0;
    fscanf(FileHandle, "%d\n", &brickCount);
    int X, Y;
    for (int i = 0; i < brickCount; i++)
    {
        Brick *brick;
        //BrickStrong tmpBrickStrong;

        fscanf(FileHandle, "%d %d %d\n", &brickType, &X, &Y);

        switch(brickType)
        {
        case BRICK:
            brick = new Brick(Frame::brick_sprite, BRICK, X, Y);
            Brick::brickList.push_back(brick);
            //brick.clean_up();
            break;
        case BRICK_STRONG:
            brick = new Brick(Frame::brickStrong_sprite, BRICK_STRONG, X, Y);
            Brick::brickList.push_back(brick);
            break;
        case BRICK_BETON:
            brick = new Brick(Frame::brickBeton_sprite, BRICK_BETON, X, Y);
            Brick::brickList.push_back(brick);
            break;
        }
    }

    fclose(FileHandle);
}

bool Frame::main_loop()
{
    log("initializing...");
    if(init() == false)
    {
        log("ERROR: init failed");
        return false;
    }
    log("loading files...");
    if(load_files() == false)
    {
        log("ERROR: files not load");
        return false;
    }

    Button *buttonBrick = new Button(100,0, brick_sprite);
    Button *buttonStrongBrick = new Button(134,0, brickStrong_sprite);
    Button *buttonBetonBrick = new Button(168,0, brickBeton_sprite);
    Button *buttonSave = new Button(34,0,sprite_btnSave);
    Button *buttonLoad = new Button(0,0,sprite_btnLoad);
    Timer fps;
    log("loop start");
    while(quit == false)
    {
        fps.Start();
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                log("quit...");
                quit = true;
            }
            buttonBrick->handle_events(event, buttonBrick_click);
            buttonStrongBrick->handle_events(event, buttonStrongBrick_click);
            buttonBetonBrick->handle_events(event, buttonBetonBrick_click);
            buttonSave->handle_events(event, buttonSave_click);
            buttonLoad->handle_events(event, buttonLoad_click);
            if(Brick::brickList.size() > 0)
            {
                for(unsigned int i = 0; i < Brick::brickList.size();i++)
                {
                    Brick::brickList[i]->handle_events(event);
                }
            }
        }
        apply_surface(0,0,bg,screen);
        //SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format,255, 255, 255));
        buttonBrick->show(screen);
        buttonStrongBrick->show(screen);
        buttonBetonBrick->show(screen);
        buttonSave->show(screen);
        buttonLoad->show(screen);
        if(Brick::brickList.size() > 0)
        {
            for(unsigned int i = 0; i < Brick::brickList.size();i++)
            {
                Brick::brickList[i]->show(screen, font);
            }
        }

        if(SDL_Flip(screen) == -1)
        {
            log("ERROR: SDL_Flip(screen) = -1");
            return false;
        }

        if(fps.Get_Ticks() < 1000/FRAMES_PER_SECOND)
        {
            SDL_Delay((1000/FRAMES_PER_SECOND) - fps.Get_Ticks());
        }
    }
    return true;
}

void Frame::exit()
{
    SDL_FreeSurface(screen);
    SDL_FreeSurface(sprite_btnSave);
    SDL_FreeSurface(sprite_btnLoad);
    SDL_FreeSurface(brick_sprite);
    SDL_FreeSurface(brickStrong_sprite);
    SDL_FreeSurface(brickBeton_sprite);
    SDL_FreeSurface(bg);
    TTF_CloseFont(font);
    TTF_Quit();
}
