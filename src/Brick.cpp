//Brick.cpp
#include "Brick.h"
#include <sstream>

std::vector<Brick*> Brick::brickList;
extern std::vector<Texture*> textureList;

Brick::Brick(int type)
{
    drag = true;
    this->sprite = sprite;
    //texture.load_from_surface(sprite);
    box.x = 300;
    box.y = 300;
    box.w = textureList[BRICK_TEX]->w;
    box.h = textureList[BRICK_TEX]->h;
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
    //coord_tex = new Texture();
}

Brick::Brick(int type, int x, int y)
{
    drag = false;
    box.x = x;
    box.y = y;
    box.w = textureList[BRICK_TEX]->w;
    box.h = textureList[BRICK_TEX]->h;
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
    //coord_tex = new Texture();
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
//    SDL_Color color = {1,0,1};
//    SDL_Color color_bg = {1,0,0};
//    for(unsigned int i = 0; i < Brick::brickList.size(); i++)
//        {
//            if(Brick::brickList[i]->get_drag() == true)
//            {
//                Texture *coord_tex = new Texture();
//                std::stringstream ss;
//                ss << "x: "
//                   << Brick::brickList[i]->get_rect().x
//                   << " y: "
//                   << Brick::brickList[i]->get_rect().y;
//                coord = TTF_RenderText_Shaded(font, ss.str().c_str(), color, color_bg);
//                coord_tex->load_from_surface(coord);
//                coord_tex->show(300,10);
//                SDL_FreeSurface(coord);
//                delete coord_tex;
//                apply_surface(300,10,coord,screen);
//            }
//        }

    //apply_surface(box.x, box.y, sprite, screen);
    //texture.show(box.x, box.y);
    switch(type)
    {
    case BRICK:
        textureList[BRICK_TEX]->show(box.x, box.y);
        break;
    case BRICK_STRONG:
        textureList[BRICK_STRONG_TEX]->show(box.x, box.y);
        break;
    case BRICK_BETON:
        textureList[BRICK_BETON_TEX]->show(box.x, box.y);
        break;
    default:
        break;
    }

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
