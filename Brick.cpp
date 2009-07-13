//Brick.cpp
#include "Brick.h"
#include <sstream>
std::vector<Brick*> Brick::brickList;

Brick::Brick(SDL_Surface *sprite, int type)
{
    drag = true;
    this->sprite = sprite;
    box.x = 300;
    box.y = 300;
    box.w = sprite->w;
    box.h = sprite->h;
    this->type = type;
    std::stringstream ss;
    for(unsigned int i = 0; i < Brick::brickList.size(); i++)
    {
        Brick::brickList[i]->set_id(i);
        ss << Brick::brickList.size();
        ss << " " << Brick::brickList[i]->get_id() << std::endl;
        log(ss.str());
    }
    coord = NULL;
}

Brick::Brick(SDL_Surface *sprite, int type, int x, int y)
{
    drag = false;
    this->sprite = sprite;
    box.x = x;
    box.y = y;
    box.w = sprite->w;
    box.h = sprite->h;
    this->type = type;
    std::stringstream ss;
    for(unsigned int i = 0; i < Brick::brickList.size(); i++)
    {
        Brick::brickList[i]->set_id(i);
        ss << Brick::brickList.size();
        ss << " " << Brick::brickList[i]->get_id() << std::endl;
        log(ss.str());
    }
    coord = NULL;
}

Brick::~Brick()
{
    //SDL_FreeSurface(sprite);
}

void Brick::handle_events(SDL_Event &event)
{
    int mouse_x, mouse_y;

    if(event.type == SDL_MOUSEMOTION)
    {
        mouse_x = event.motion.x;
        mouse_y = event.motion.y;
    }
    if(event.type == SDL_MOUSEBUTTONDOWN)
    {
        if(event.button.button == SDL_BUTTON_LEFT)
        {
            mouse_x = event.button.x;
            mouse_y = event.button.y;
            if((mouse_x > box.x)&&(mouse_y > box.y)&&
                (mouse_x < box.x+box.w)&&(mouse_y < box.y+box.h))
            {
                drag = true;
            }
        }
        if(event.button.button == SDL_BUTTON_RIGHT)
        {
            mouse_x = event.button.x;
            mouse_y = event.button.y;
            if((mouse_x > box.x)&&(mouse_y > box.y)&&
                (mouse_x < box.x+box.w)&&(mouse_y < box.y+box.h))
            {
                drag = true;
                for(unsigned int i = 0; i < Brick::brickList.size(); i++)
                {
                    if(Brick::brickList[i]->get_drag() == true)
                    {
                        Brick::brickList.erase(Brick::brickList.begin() + i);
                    }
                }
            }
        }
    }
    if(event.type == SDL_MOUSEBUTTONUP)
    {
        drag = false;
    }
    if(drag == true)
    {
        box.x = mouse_x - box.w/2;
        box.y = mouse_y - box.h/2;
    }
}

void Brick::show(SDL_Surface *screen, TTF_Font *font)
{
    SDL_Color color = {0,0,0};
    for(unsigned int i = 0; i < Brick::brickList.size(); i++)
        {
            if(Brick::brickList[i]->get_drag() == true)
            {
                std::stringstream ss;
                ss << "x: "
                   << Brick::brickList[i]->get_rect().x
                   << " y: "
                   << Brick::brickList[i]->get_rect().y;
                coord = TTF_RenderText_Solid(font, ss.str().c_str(), color);
                apply_surface(300,10,coord,screen);
            }
        }

    apply_surface(box.x, box.y, sprite, screen);
}

SDL_Rect Brick::get_rect()
{
    return box;
}

int Brick::get_type()
{
    return type;
}

int Brick::get_id()
{
    return id;
}

void Brick::set_id(int i)
{
    this->id = i;
}

void Brick::set_up(int x, int y)
{
    box.x = x;
    box.y = y;
}
