//Texture.cpp

#include "Texture.h"
#include "SDLUtils.h"
#include <sstream>

std::stringstream st;


Texture::~Texture()
{
    glDeleteTextures( 1, &texture);
}

bool Texture::load_from_file(std::string filename)
{
    int mode;
    int width = 0;
    int height = 0;

    SDL_Surface *surface;
    surface = IMG_Load(filename.c_str());
    if(surface == NULL)
    {
        log("ERROR: " + filename + "not load");
        return false;
    }

    if(surface->format->BytesPerPixel == 4) // 32bit
    {
        mode = GL_RGBA;
    }
    else if(surface->format->BytesPerPixel == 3) //24bit
    {
        mode = GL_RGB;
    }
    else
    {
        log("ERROR: " + filename + " not 32 or 24 bit image");
        SDL_FreeSurface(surface);
        return false;
    }
    w = surface->w;
    h = surface->h;

    //Check that the image's width is a power of 2
    while ( ((surface->w+width) & (surface->w+width - 1)) != 0 )
    {
        width++;
    }

    // Also check if the height is a power of 2
    while ( (surface->h+height & (surface->h+height - 1)) != 0 )
    {
        height++;
    }

    SDL_Surface *temp = SDL_CreateRGBSurface(SDL_SWSURFACE, surface->w+width, surface->h+height, surface->format->BitsPerPixel,
                                                surface->format->Rmask,surface->format->Gmask,surface->format->Bmask,surface->format->Amask);
    SDL_Rect offset;
    offset.x = 0;
    offset.y = 0;

    SDL_BlitSurface(surface, NULL, temp, &offset);

    // Have OpenGL generate a texture object handle for us
    glGenTextures( 1, &texture );

    // Bind the texture object
    glBindTexture( GL_TEXTURE_2D, texture );

    // Set the texture's stretching properties
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    // Edit the texture object's image data using the information SDL_Surface gives us
    glTexImage2D( GL_TEXTURE_2D, 0, mode, temp->w, temp->h, 0,
                      mode, GL_UNSIGNED_BYTE, temp->pixels );

    wdt = (float)surface->w/((float)surface->w+(float)width);
    hgt = (float)surface->h/((float)surface->h+(float)height);

    SDL_FreeSurface(temp);
    SDL_FreeSurface(surface);
    return true;
}

bool Texture::load_from_surface(SDL_Surface *surface)
{
    int mode;
    if(surface == NULL)
    {
        log("ERROR: surface is NULL");
        return false;
    }
    if(surface->format->BytesPerPixel == 4) // 32bit
    {
        mode = GL_RGBA;
    }
    else if(surface->format->BytesPerPixel == 3) //24bit
    {
        mode = GL_RGB;
    }
    else
    {
        log("ERROR: surface not 32 or 24 bit image");
        SDL_FreeSurface(surface);
        return false;
    }

    int width = 0;
    int height = 0;
    w = surface->w;
    h = surface->h;



    //Check that the image's width is a power of 2
    while ( ((surface->w+width) & (surface->w+width - 1)) != 0 )
    {
        width++;
    }

    // Also check if the height is a power of 2
    while ( (surface->h+height & (surface->h+height - 1)) != 0 )
    {
        height++;
    }

    SDL_Surface *temp = SDL_CreateRGBSurface(SDL_SWSURFACE, surface->w+width, surface->h+height, surface->format->BitsPerPixel,
                                                surface->format->Rmask,surface->format->Gmask,surface->format->Bmask,surface->format->Amask);
    SDL_Rect offset;
    offset.x = 0;
    offset.y = 0;

    SDL_BlitSurface(surface, NULL, temp, &offset);

    // Have OpenGL generate a texture object handle for us
    glGenTextures( 1, &texture );

    // Bind the texture object
    glBindTexture( GL_TEXTURE_2D, texture );

    // Set the texture's stretching properties
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    // Edit the texture object's image data using the information SDL_Surface gives us
    glTexImage2D( GL_TEXTURE_2D, 0, mode, temp->w, temp->h, 0,
                      mode, GL_UNSIGNED_BYTE, temp->pixels );

    wdt = (float)surface->w/((float)surface->w+(float)width);
    hgt = (float)surface->h/((float)surface->h+(float)height);

    SDL_FreeSurface(temp);
    SDL_FreeSurface(surface);
    return true;
}

void Texture::show(int x, int y)
{
    glPushMatrix();
    glTranslatef(x,y,0);
    //glColor4f(1.0f, 1.0f, 1.0f, 0.1f);
    glBindTexture(GL_TEXTURE_2D, texture);

    glBegin(GL_QUADS);

        //glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
        glTexCoord2f( 0, 0 );
        glVertex3f( 0, 0, 0.0f );

        //Bottom-left vertex (corner)
        glTexCoord2f( wdt, 0 );
        glVertex3f( w, 0, 0 );

        //Bottom-right vertex (corner)
        glTexCoord2f( wdt, hgt );
        glVertex3f( w, h, 0 );

        //Top-right vertex (corner)
        glTexCoord2f( 0, hgt );
        glVertex3f( 0, h, 0 );

        //glVertex3f( 50, 50, 0 );
        glEnd();

        glLoadIdentity();
        glPopMatrix();
}
