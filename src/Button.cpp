/*
 *      Button.cpp
 *
 *      Copyright 2009 Sergey Babneev <plughead@mail.ru>
 *      Copyright 2009-2011 Maxim Kachur <mcdebugger@duganet.ru>
 *
 *      This file is part of Arkilleved.
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

#include "Button.h"

extern std::ofstream loger;
extern int stateID;
extern int nextState;
extern std::vector<Texture> textureList;

Button::Button(int x, int y, std::string filename)
{
	buttonSheet = image_load(filename, 0xFF, 0, 0xFF);
	if(buttonSheet == NULL)
	{
		log("ERROR: button image not loaded!");
		stateID = STATE_EXIT;
	}
	texture->load_from_surface(buttonSheet);

//	clips[CLIP_MOUSEOVER].x = 0;
//	clips[CLIP_MOUSEOVER].y = 0;
//	clips[CLIP_MOUSEOVER].w = textureList[BTN_SAVE_TEX]->w;
//	clips[CLIP_MOUSEOVER].h = textureList[BTN_SAVE_TEX]->h/2;
//
//	clips[CLIP_MOUSEOUT].x = 0;
//	clips[CLIP_MOUSEOUT].y = textureList[BTN_SAVE_TEX]->h/2;
//	clips[CLIP_MOUSEOUT].w = textureList[BTN_SAVE_TEX]->w;
//	clips[CLIP_MOUSEOUT].h = textureList[BTN_SAVE_TEX]->h;

	box.x = x;
	box.y = y;
	box.w = buttonSheet->w;
	box.h = buttonSheet->h/2;

	//clip = clips[CLIP_MOUSEOUT];
}

Button::Button(int x, int y, Texture* texture, int num_clips)
{
	this->texture = new Texture();
	this->texture = texture;
	this->num_clips = num_clips;
	if(num_clips > 2)
		num_clips = 2;

	clips[CLIP_MOUSEOVER].x = 0;
	clips[CLIP_MOUSEOVER].y = 0;
	clips[CLIP_MOUSEOVER].w = texture->w;
	clips[CLIP_MOUSEOVER].h = texture->h/num_clips;

	if(num_clips > 1)
	{
		clips[CLIP_MOUSEOUT].x = 0;
		clips[CLIP_MOUSEOUT].y = texture->h/num_clips;
		clips[CLIP_MOUSEOUT].w = texture->w;
		clips[CLIP_MOUSEOUT].h = texture->h;
		clip = clips[CLIP_MOUSEOUT];
	}
	else
	clip = clips[CLIP_MOUSEOVER];

	box.x = x;
	box.y = y;
	box.w = texture->w;
	box.h = texture->h/num_clips;
}

Button::~Button()
{
   delete texture;
}

void Button::handle_events(SDL_Event &event,void(callback)(void))
{
	//mouse_offsets
	int mouse_x,mouse_y;

	if(event.type == SDL_MOUSEMOTION)
	{
		mouse_x = event.motion.x;
		mouse_y = event.motion.y;

		if((mouse_x > box.x)&&(mouse_y > box.y)&&
		   (mouse_x < box.x+box.w)&&(mouse_y < box.y+box.h))
		{
			clip = clips[CLIP_MOUSEOVER];
		}
		else
		{
			clip = clips[CLIP_MOUSEOUT];
		}
	}
	if(event.type == SDL_MOUSEBUTTONDOWN)
	{
		if((event.button.button == SDL_BUTTON_LEFT) || (event.button.button == SDL_BUTTON_MIDDLE))
		{
			mouse_x = event.button.x;
			mouse_y = event.button.y;
			if((mouse_x > box.x)&&(mouse_y > box.y)&&
				(mouse_x < box.x+box.w)&&(mouse_y < box.y+box.h))
			{
				//clip = clips[MOUSE_DOWN];
				callback();
			}
		}
	}
//	if(event.type == SDL_MOUSEBUTTONDOWN)
//	{
//		if(event.type == SDL_BUTTON_LEFT)
//		{
//			mouse_x = event.button.x;
//			mouse_y = event.button.y;
//			if((mouse_x > box.x)&&(mouse_y > box.y)&&
//				(mouse_x < box.x+box.w)&&(mouse_y < box.y+box.w))
//			{
//				//clip = clips[MOUSE_UP];
//			}.y;
//			if((mouse_x > box.x)&&(mouse_y > box.y)&&
//				(mouse_x < box.x+box.w)&&(mouse_y < box.y+box.w))
//			{
//				//clip = clips[MOUSE_UP];
//			}
//		}
//	}
}

void Button::show()
{
	if(num_clips > 1)
	{
		texture->show(box.x,box.y, clip);
	}
	else
	{
		texture->show(box.x,box.y);
	}
}
