/*
 *      Frame.cpp
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

#include "Frame.h"
#include <file.hpp>
#include <fstream>
#include <sstream>

extern std::vector<Texture*> textureList;
//extern std::vector<Brick*> Brick::brickList;

Frame::Frame()
{
	screen = NULL;
	quit   = false;
	//font = NULL;
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
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0,0,0,1);
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

	if(initGL() == false)
	{
		return false;
	}
	return true;
}

bool Frame::load_files()
{
	std::string filename;
	//-----------------------------------------------------------
	filename = path_construct("images", "brick.png");
	Texture *brick_tex = new Texture;
	if(brick_tex->load_from_file(filename) == false)
	{
		log("ERROR: " + filename + " not found");
		return false;
	}
	textureList.push_back(brick_tex);
	//-----------------------------------------------------------
	filename = path_construct("images", "brick_strong.png");
	Texture *brickStrong_tex = new Texture;
	if(brickStrong_tex->load_from_file(filename) == false)
	{
		log("ERROR: " + filename + " not found");
		return false;
	}
	textureList.push_back(brickStrong_tex);
	//-----------------------------------------------------------
	filename = path_construct("images", "brick_beton.png");
	Texture *brickBeton_tex = new Texture;
	if(brickBeton_tex->load_from_file(filename) == false)
	{
		log("ERROR: " + filename + " not found");
		return false;
	}
	textureList.push_back(brickBeton_tex);
	//-----------------------------------------------------------
	filename = path_construct("images", "brick_portal_a.png");
	Texture *brickPortalA_tex = new Texture;
	if(brickPortalA_tex->load_from_file(filename) == false)
	{
		log("ERROR: " + filename + " not found");
		return false;
	}
	textureList.push_back(brickPortalA_tex);
	//-----------------------------------------------------------
	filename = path_construct("images", "brick_portal_b.png");
	Texture *brickPortalB_tex = new Texture;
	if(brickPortalB_tex->load_from_file(filename) == false)
	{
		log("ERROR: " + filename + " not found");
		return false;
	}
	textureList.push_back(brickPortalB_tex);
	//-----------------------------------------------------------
	filename = path_construct ("images", "button_save.png");
	Texture *btnSave_tex = new Texture;
	if(btnSave_tex->load_from_file(filename) == false)
	{
		log("ERROR: " + filename + " not found");
		return false;
	}
	textureList.push_back(btnSave_tex);
	//-----------------------------------------------------------
	filename = path_construct("images", "button_open.png");
	Texture *btnLoad_tex = new Texture;
	if(btnLoad_tex->load_from_file(filename) == false)
	{
		log("ERROR: " + filename + " not found");
		return false;
	}
	textureList.push_back(btnLoad_tex);
	//-----------------------------------------------------------
	filename = path_construct("images", "bg.png");
	Texture *bg_tex = new Texture;
	if(bg_tex->load_from_file(filename) == false)
	{
		log("ERROR: " + filename + " not found");
		return false;
	}
	textureList.push_back(bg_tex);
	//-----------------------------------------------------------
	filename = path_construct("fonts", "aerial.ttf");
	font.open(filename.c_str(), 10);
//	if(font == NULL)
//	{
//		log("ERROR: " + fontsdir + "/aerial.ttf not found");
//		return false;
//	}
	return true;
}


void buttonBrick_click()
{
	Brick *brick = new Brick(BRICK);
	Brick::brickList.push_back(brick);
}

void buttonStrongBrick_click()
{
	Brick *brick = new Brick(BRICK_STRONG);
	Brick::brickList.push_back(brick);
}

void buttonBetonBrick_click()
{
	Brick *brick = new Brick(BRICK_BETON);
	Brick::brickList.push_back(brick);
}

void buttonBrickPortalA_click()
{
	Brick *brick = new Brick(BRICK_PORTAL_A);
	Brick::brickList.push_back(brick);
}
void buttonBrickPortalB_click()
{
	Brick *brick = new Brick(BRICK_PORTAL_B);
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
	if(Brick::brickList.size() > 0)
	{
		for(unsigned int i = 0; i < Brick::brickList.size(); i++)
		{
		   Brick::brickList.erase(Brick::brickList.begin(), Brick::brickList.end());
		}
	}

	FILE *FileHandle = fopen("level.map", "r");

	int brickCount = 0;
	int brickType  = 0;
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
			brick = new Brick(BRICK, X, Y);
			Brick::brickList.push_back(brick);
			//brick.clean_up();
			break;
		case BRICK_STRONG:
			brick = new Brick(BRICK_STRONG, X, Y);
			Brick::brickList.push_back(brick);
			break;
		case BRICK_BETON:
			brick = new Brick(BRICK_BETON, X, Y);
			Brick::brickList.push_back(brick);
			break;
		case BRICK_PORTAL_A:
			brick = new Brick(BRICK_PORTAL_A, X, Y);
			Brick::brickList.push_back(brick);
			break;
		case BRICK_PORTAL_B:
			brick = new Brick(BRICK_PORTAL_B, X, Y);
			Brick::brickList.push_back(brick);
			break;
		}
	}

	fclose(FileHandle);
}

int Frame::get_grid(char axis, int coord)
{
	int grid_startx, grid_starty, grid_stepx, grid_stepy;
	int grid_coord;
	switch(axis)
	{
		case 'x':
			grid_startx = 22;
			grid_stepx  = 29;
			grid_coord  = grid_stepx * (coord / grid_stepx - 1) + grid_startx;
			break;
		case 'y':
			grid_starty = 53;
			grid_stepy  = 29;
			grid_coord  = grid_stepy * (coord / grid_stepy - 2) + grid_starty;
			break;
	}
	return grid_coord;
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
	log("Creating buttons...");
	Button *buttonBrick = new Button(106,6, textureList[BRICK_TEX]);
	Button *buttonStrongBrick = new Button(140,6, textureList[BRICK_STRONG_TEX]);
	Button *buttonBetonBrick = new Button(174,6, textureList[BRICK_BETON_TEX]);
	Button *buttonBrickPortalA = new Button(208,6, textureList[BRICK_PORTAL_A_TEX]);
	Button *buttonBrickPortalB = new Button(242,6, textureList[BRICK_PORTAL_B_TEX]);
	Button *buttonSave = new Button(40,6,textureList[BTN_SAVE_TEX],2);
	Button *buttonLoad = new Button(6,6,textureList[BTN_LOAD_TEX],2);
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
			buttonBrickPortalA->handle_events(event, buttonBrickPortalA_click);
			buttonBrickPortalB->handle_events(event, buttonBrickPortalB_click);
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

		buttonBrick->show();
		buttonStrongBrick->show();
		buttonBetonBrick->show();
		buttonBrickPortalA->show();
		buttonBrickPortalB->show();
		buttonSave->show();
		buttonLoad->show();
		if(Brick::brickList.size() > 0)
		{
			for(unsigned int i = 0; i < Brick::brickList.size();i++)
			{
				Brick::brickList[i]->show(screen, &font);
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
	font.release();
	for(unsigned int i = 0; i < Brick::brickList.size(); i++)
	{
	   Brick::brickList.erase(Brick::brickList.begin(), Brick::brickList.end());
	}

	for(unsigned int i = 0; i < textureList.size(); i++)
	{
	   textureList.erase(textureList.begin(), textureList.end());
	}
	SDL_Quit();
}
