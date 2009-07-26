//Frame.cpp
//#include "config.h"
#include "Frame.h"
#include <fstream>
#include <sstream>

SDL_Surface* Frame::brickStrong_sprite;
SDL_Surface* Frame::brick_sprite;
SDL_Surface* Frame::brickBeton_sprite;
extern std::vector<Texture*> textureList;
//extern std::vector<Brick*> Brick::brickList;

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

bool Frame::initGL()
{
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
    glEnable( GL_TEXTURE_2D );
    glClearColor(1,1,1,1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,SCREEN_WIDTH, SCREEN_HEIGHT, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if(glGetError() != GL_NO_ERROR)
    {
        log("ERROR: gl not init, " + glGetError());
        return false;
    }
    return true;
}

bool Frame::init()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        log("ERROR: init failed");
        return false;
    }
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_OPENGL);
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

    if(initGL() == false)
    {
        return false;
    }
    return true;
}

bool Frame::load_files()
{
    std::string fontsdir, imagedir, font_filename, img_filename;
    #ifdef WIN32
    imagedir = "images";
    fontsdir = "fonts";
    #else
    /*imagedir = "../share/" + PACKAGE + "/images";
    fontsdir = "../share/" + PACKAGE + "/fonts";*/
    imagedir = "../share/arkilloid-leveledit/images";
    fontsdir = "../share/arkilloid-leveledit/fonts";
    #endif
    img_filename = imagedir + "/brick.png";
    brick_sprite = IMG_Load(img_filename.c_str());
    if(brick_sprite == NULL)
    {
        log(img_filename + " not found");
        return false;
    }
    Texture *texture = new Texture();
    texture->load_from_surface(brick_sprite);
    textureList.push_back(texture);
    SDL_FreeSurface(brick_sprite);

    img_filename = imagedir + "/brick_strong.png";
    brickStrong_sprite = IMG_Load(img_filename.c_str());
    if(brickStrong_sprite == NULL)
    {
        log(img_filename + " not found");
        return false;
    }
    Texture *texture1 = new Texture();
    texture1->load_from_surface(brickStrong_sprite);
    textureList.push_back(texture1);
    SDL_FreeSurface(brickStrong_sprite);

    img_filename = imagedir + "/brick_beton.png";
    brickBeton_sprite = IMG_Load(img_filename.c_str());
    if(brickBeton_sprite == NULL)
    {
        log(img_filename + " not found");
        return false;
    }
    Texture *texture2 = new Texture();
    texture2->load_from_surface(brickBeton_sprite);
    textureList.push_back(texture2);
    SDL_FreeSurface(brickBeton_sprite);

    img_filename = imagedir + "/button_save.png";
    sprite_btnSave = IMG_Load(img_filename.c_str());
    if(sprite_btnSave == NULL)
    {
        log(img_filename + " not found");
        return false;
    }
    Texture *texture3 = new Texture();
    texture3->load_from_surface(sprite_btnSave);
    textureList.push_back(texture3);
    SDL_FreeSurface(sprite_btnSave);

    img_filename = imagedir + "/button_open.png";
    sprite_btnLoad = IMG_Load(img_filename.c_str());
    if(sprite_btnLoad == NULL)
    {
        log(img_filename + " not found");
        return false;
    }
    Texture *texture4 = new Texture();
    texture4->load_from_surface(sprite_btnLoad);
    textureList.push_back(texture4);
    //SDL_FreeSurface(sprite_btnLoad);

    img_filename = imagedir + "/bg.png";
    bg = IMG_Load(img_filename.c_str());
    if(bg == NULL)
    {
        log(img_filename + " not found");
        return false;
    }
    Texture *texture5 = new Texture();
    texture5->load_from_surface(bg);
    textureList.push_back(texture5);
    SDL_FreeSurface(bg);

    font_filename = fontsdir + "/aerial.ttf";
    font = TTF_OpenFont(font_filename.c_str(), 10);
    if(font == NULL)
    {
        log("ERROR: " + fontsdir + "/aerial.ttf not found");
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
    Button *buttonBrick = new Button(100,0, textureList[BRICK_TEX]);
    Button *buttonStrongBrick = new Button(134,0, textureList[BRICK_STRONG_TEX]);
    Button *buttonBetonBrick = new Button(168,0, textureList[BRICK_BETON_TEX]);
    Button *buttonSave = new Button(34,0,textureList[BTN_SAVE_TEX]);
    Button *buttonLoad = new Button(0,0,textureList[BTN_LOAD_TEX]);
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
        glClear(GL_COLOR_BUFFER_BIT);
        textureList[BG_TEX]->show(0,0);
//        apply_surface(0,0,bg,screen);
//        SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format,255, 255, 255));
        buttonBrick->show();
        buttonStrongBrick->show();
        buttonBetonBrick->show();
        buttonSave->show();
        buttonLoad->show();
        if(Brick::brickList.size() > 0)
        {
            for(unsigned int i = 0; i < Brick::brickList.size();i++)
            {
                Brick::brickList[i]->show(screen, font);
            }
        }

        SDL_GL_SwapBuffers();

        if(fps.Get_Ticks() < 1000/FRAMES_PER_SECOND)
        {
            SDL_Delay((1000/FRAMES_PER_SECOND) - fps.Get_Ticks());
        }
    }
    //exit();
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

    for(unsigned int i = 0; i < Brick::brickList.size(); i++)
    {
       Brick::brickList.erase(Brick::brickList.begin(), Brick::brickList.end());
    }

    for(unsigned int i = 0; i < textureList.size(); i++)
    {
       textureList.erase(textureList.begin(), textureList.end());
    }
    TTF_Quit();
    SDL_Quit();
}
