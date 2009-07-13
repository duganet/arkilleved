#include "SDLUtils.h"

std::ofstream loger("log.txt");
void log(std::string message)
{
    loger << message << std::endl;

    loger.flush();
}

int stateID = STATE_NULL;
int nextState = STATE_NULL;

int lives = 3;
int score = 0;
int hi_score = 0;

SDL_Surface *image_load(std::string filename)
{
    SDL_Surface *loadedImage = NULL;
    SDL_Surface *optimizedImage = NULL;

    loadedImage = IMG_Load(filename.c_str());
    if(loadedImage != NULL)
    {
        optimizedImage = SDL_DisplayFormat(loadedImage);
        SDL_FreeSurface(loadedImage);
    }
    return optimizedImage;
}

SDL_Surface *image_load(std::string filename, int red, int green, int blue)
{

    SDL_Surface *loadedImage = NULL;
    SDL_Surface *optimizedImage = NULL;

    loadedImage = IMG_Load(filename.c_str());

    if(loadedImage != NULL)
    {

        optimizedImage = SDL_DisplayFormat(loadedImage);

        SDL_FreeSurface(loadedImage);
    }


    if(optimizedImage != NULL)
    {
        Uint32 colorKey = SDL_MapRGB(optimizedImage->format, red, green, blue);
        SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, colorKey);
    }

    return optimizedImage;
}

void apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *destination)
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface(source, NULL, destination, &offset);
}

void apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip)
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface(source, clip, destination, &offset);
}

bool check_collision( SDL_Rect A, SDL_Rect B )
{

    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;


    leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;


    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;

    if( bottomA < topB )
    {
        return false;
    }

    if( topA > bottomB )
    {
        return false;
    }

    if( rightA < leftB )
    {
        return false;
    }

    if( leftA > rightB )
    {
        return false;
    }


    return true;
}
int finde_zone( SDL_Rect A, SDL_Rect B )
{
    int leftA,leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA   = A.x;
    rightA  = A.x+A.w;
    topA    = A.y;
    bottomA = A.y+A.h;

    leftB   = B.x;
    rightB  = B.x+B.w;
    topB    = B.y;
    bottomB = B.y+B.h;

    if(B.x < leftA && B.y > topA)
    {
        return ZONE_A;
    }
    return 0;
}


