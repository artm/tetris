/*
 * slak-games: simple SDL+OpenGL based games
 * Copyright (C) 2006-2008 Artem Baguinski <femistofel@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include <iostream>
#include <sstream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "slak/glui/gl-include.h"
#include "renderer.h"
#include "tetris.h"
#include "tetris_app.h"
#include "slak/glui/app.h"
#include "slak/glui/rgbpic.h"

using namespace slak::tetris;
using namespace slak::glui;

Renderer::Renderer(Game * g)
	: g(g), score_lbl(TetrisApp::fontname, 24),
	  level_lbl(TetrisApp::fontname, 48)
{
  // here we position the widgets and calculate the positions of the field
	int field_pixel_width = block_size * g->field.width;
	int field_pixel_height = block_size * g->field.height;
	field_x0 = (App::getScreenWidth() - field_pixel_width) / 2;
	field_x1 = App::getScreenWidth() - field_x0;
	field_y0 = (App::getScreenHeight() - field_pixel_height) / 2;
	field_y1 = App::getScreenHeight() - field_y0;

	score_lbl.x = field_x1 + block_size;
	score_lbl.y = field_y1;

  // position the level text overlay using extents of "00" string
  // hoping they'll never get to 100
	int lw, lh;
	TTF_SizeText(level_lbl.fnt, "00", &lw, &lh);
	level_lbl.x = field_x0 - block_size - lw;
	level_lbl.y = field_y1;

	loadTextures();
}

Renderer::~Renderer()
{
}

char * color_names[] = {
	"none",
	"red",
	"black",
	"magenta",
	"blue",
	"green",
	"brown",
	"cyan",
};

void Renderer::loadTextures()
{
	glGenTextures(N_STATES-1, (GLuint*)texture_ids);
	for(int i=1; i<N_STATES; i++) {
		std::string fname =
			std::string("media/bitmaps/tetris-block-") +
			color_names[i] + ".png";
		SDL_Surface * img = IMG_Load(fname.c_str());
		assert(img);
		glBindTexture(GL_TEXTURE_2D, texture_ids[i]);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		unsigned int texfmt, fmt, tp;
		// find opengl format from sdl pixel format
		sdl2glPixelParams(img->format, fmt, tp);
		texfmt = (fmt == GL_BGR) ?  GL_RGB : GL_RGBA;
		glTexImage2D(GL_TEXTURE_2D,
			     0, texfmt, img->w, img->h,
			     0, fmt, tp, img->pixels);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
				GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
				GL_NEAREST);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	}
}

void Renderer::draw()
{
        // prepare
	glColor3f(0,0,0);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glLineWidth(3.0);

	// delegate the actual work
	drawField();
	drawBlocks();
	drawScore();
	drawLevel();
	drawNextTetrad();
}

void Renderer::drawField()
{
	glBegin(GL_LINE_STRIP);
	glVertex2i(field_x0, field_y1);
	glVertex2i(field_x0, field_y0);
	glVertex2i(field_x1, field_y0);
	glVertex2i(field_x1, field_y1);
	glEnd();
}

void Renderer::drawBlocksPass(square_state st, float x0, float y0)
{
	glBegin(st==EMPTY?GL_POINTS:GL_QUADS);

	// loop over the game field and only draw the squares in given state
	for(int j=0; j<g->field.height; j++) {
		if (g->state == STROBE_FX_STATE
		    && g->field.lineComplete(j)
		    && ((g->fall_ticks / 10 % 2)==0))
			continue;
		for(int i=0; i<g->field.width; i++) {
			if (g->field.sq(i,j) == st) {
				float x,y;
				blockXY(i,j,x,y,x0,y0);
				if (st==EMPTY)
				  // empty squares are points
					glVertex2f(x,y);
				else {
				  // all that optimization for nothing - rendering a textured square
					glTexCoord2f(0,1);
					glVertex2f(x - block_size/2,y - block_size/2);
					glTexCoord2f(0,0);
					glVertex2f(x - block_size/2,y + block_size/2-1);
					glTexCoord2f(1,0);
					glVertex2f(x + block_size/2-1,y + block_size/2-1);
					glTexCoord2f(1,1);
					glVertex2f(x + block_size/2-1,y - block_size/2);
				}
			}
		}
	}
	glEnd();
}

void Renderer::drawNextTetrad()
{
	int x0 = field_x1 + block_size,
	    y0 = field_y1 - 8 * block_size;

	glEnable(GL_TEXTURE_2D);
	// at this point we don't know which texture it'll be ...
	bool colour_set = false;
	for(int j=0; j<g->nextTetrad.height; j++) {
		for(int i=0; i<g->nextTetrad.width; i++) {
			if (g->nextTetrad.sq(i,j) != EMPTY) {
				float x,y;
				if (!colour_set) {
				  // ... here we figured it
					glBindTexture(GL_TEXTURE_2D, texture_ids[g->nextTetrad.sq(i,j)]) ;
					glBegin(GL_QUADS);
				  // only have to set it once
					colour_set = true;
				}

				blockXY(i,j,x,y,x0,y0);
				// a textured square
				glTexCoord2f(0,1);
				glVertex2f(x - block_size/2,y - block_size/2);
				glTexCoord2f(0,0);
				glVertex2f(x - block_size/2,y + block_size/2-1);
				glTexCoord2f(1,0);
				glVertex2f(x + block_size/2-1,y + block_size/2-1);
				glTexCoord2f(1,1);
				glVertex2f(x + block_size/2-1,y - block_size/2);
			}
		}
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void Renderer::drawBlocks()
{
	glPointSize(5.0);
	glEnable(GL_POINT_SMOOTH);
	drawBlocksPass(EMPTY);

	glEnable(GL_TEXTURE_2D);
	for(int i = RED; i < N_STATES; i++) {
		glBindTexture(GL_TEXTURE_2D, texture_ids[i]);
		drawBlocksPass((square_state)i);
	}
	glDisable(GL_TEXTURE_2D);
}

void Renderer::drawLevel()
{
  // make a string
	std::ostringstream os;
	os.width(2);
	os.fill('0');
	os << g->level;

  // ...render it
	level_lbl.setText(os.str());
	level_lbl.draw();
}

void Renderer::drawScore()
{
  // make a string
	std::ostringstream os;
	os.width(8);
	os.fill('0');
	os << g->score;

  // render it
	score_lbl.setText(os.str());
	score_lbl.draw();
}

void Renderer::blockXY(int i, int j, float& x, float& y, float x0, float y0)
{
	if (x0 < 0) x0 = (float)field_x0;
	if (y0 < 0) y0 = (float)field_y0;
	x = x0 + i*block_size + 0.5f*block_size;
	y = y0 + j*block_size + 0.5f*block_size;
}


