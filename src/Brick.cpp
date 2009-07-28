/*
 *      Brick.cpp
 *
 *      Copyright 2009 PlugHead Games <plughead@mail.ru>
 *      Copyright 2009 DUGA Project <dev@duganet.ru>
 *
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License
 *      along with this program; if not, write to the Free Software
 *      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *      MA 02110-1301, USA.
 */

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

void Brick::show(SDL_Surface *screen, GLFT_Font *font)
{
    for(unsigned int i = 0; i < Brick::brickList.size(); i++)
    {
            if(Brick::brickList[i]->get_drag() == true)
            {
                glColor3f(0,0,0);
                font->beginDraw(300,10) << "x: "
                                        << Brick::brickList[i]->get_rect().x
                                        << " y: "
                                        << Brick::brickList[i]->get_rect().y
                                        << font->endDraw();
                glColor3f(1,1,1);
            }
    }
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
