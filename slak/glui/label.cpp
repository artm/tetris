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
#include "gl-include.h"
#include <SDL.h>
#include <SDL_ttf.h>

#include "label.h"

using namespace slak::glui;

Label::Label(std::string fontname, int fontsize, int fontstyle,int al)
	: fnt(NULL), bitmap(NULL), text(""), x(0), y(0), align(al)
{
	if ((fnt = TTF_OpenFont(fontname.c_str(),fontsize)) == NULL) {
		std::cerr << "Can't open font file: "
			<< SDL_GetError() << "\n";
		exit(1);
	}
	TTF_SetFontStyle(fnt, fontstyle);
}

Label::~Label()
{
	if (fnt)
		TTF_CloseFont(fnt);
	if (bitmap)
		SDL_FreeSurface(bitmap);
}

void Label::setText(std::string newtext)
{
	if (newtext != text) {
		SDL_Color black = {0,0,0};
		text = newtext;

		if (bitmap)
			SDL_FreeSurface(bitmap);
		bitmap =
			TTF_RenderText_Blended(fnt,text.c_str(),black);
	}
}

void Label::draw()
{
	int ax,ay = y;
	switch(align) {
	case ALIGN_LEFT:
		ax = x;
		break;
	case ALIGN_RIGHT:
		ax = x - bitmap->w;
		break;
	case ALIGN_CENTER:
		ax = x - bitmap->w/2;
		break;
	}
	glRasterPos2i(ax,ay);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glPixelZoom(1, -1);
	glDrawPixels(bitmap->w, bitmap->h, GL_BGRA,
		     GL_UNSIGNED_INT_8_8_8_8_REV,
		     bitmap->pixels);

}

