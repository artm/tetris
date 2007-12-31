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

#include <sstream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <assert.h>
#include "gl-include.h"
#include "hiscore_screen.h"
#include "label.h"
#include "app.h"
#include "orthomode.h"

using namespace slak::glui;

HiScoreScreen::HiScoreScreen(HiScoreTable * t, unsigned int leave, std::string fontname)
	: table(t),
	  leave_message(leave),
	  cursor_pulse(cursor_delay)
{
	int x_nums=-1, x_names, x_scores, y;
	for(int i = 0; i < table->records.size(); i++) {
		int w,h;
		Label * labl = new Label(fontname,32);
		if (x_nums<0) {
			TTF_SizeText(labl->fnt,
				     "00oOOOOo00000000",
				     &w,&h);
			x_nums = App::getScreenWidth()/2 - w/2;
			x_scores = x_nums+w;
			TTF_SizeText(labl->fnt,
				     "00oOO",
				     &w,&h);
			x_names = x_nums + w;
		}
		y = App::getScreenHeight()/2 + (5 - i)*(h+2);

		labl->x = x_nums;
		labl->y = y;
		std::ostringstream os;
		os.width(2);
		os.fill(' ');
		os << i+1;
		labl->setText(os.str());
		overlays.push_back(labl);

		labl = new Label(fontname,32);
		labl->x = x_names;
		labl->y = y;
		labl->setText("....");
		labl->align = Label::ALIGN_CENTER;
		overlays.push_back(labl);
		nameLabels.push_back(labl);

		labl = new Label(fontname,32);
		labl->x = x_scores;
		labl->y = y;
		labl->align = Label::ALIGN_RIGHT;
		labl->setText("00000000");
		overlays.push_back(labl);
		scoreLabels.push_back(labl);
	}

	modes.push_back(new OrthoMode);
}

bool HiScoreScreen::handle(SDL_Event& ev)
{
	switch(ev.type) {
	case SDL_KEYDOWN:
		if (table->last_record) {
			if ((ev.key.keysym.sym>='0'
			     && ev.key.keysym.sym<='9')
			    ||(ev.key.keysym.sym>='a'
			       && ev.key.keysym.sym<='z')
			    ||(ev.key.keysym.sym>='A'
			       && ev.key.keysym.sym<='Z')) {
				if (table->last_record->cursor < 4) {
					table->last_record ->
						name[table->last_record->
						cursor] = ev.key.keysym.sym;
					table->last_record->cursor++;
				}
				return true;

			}

			switch(ev.key.keysym.sym) {
			case SDLK_RETURN:
				goto leave_screen;
			case SDLK_BACKSPACE:
				if (table->last_record->cursor>0)
					table->last_record->name[--table->last_record->cursor] = '.';
				return true;
			}
		} else
			goto leave_screen;
		break;

	}
	return Screen::handle(ev);

leave_screen:
	table->last_record = NULL;
	table->save();
	App::push(leave_message);
	return true;
}

void HiScoreScreen::draw()
{
	bool show_cursor = cursor_pulse.getState();

	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0,0,0);

	glLineWidth(3.0);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for(int i = 0; i < table->records.size(); i++) {
		HiScoreTable::Record& r = table->records[i];

		std::string text = r.name;
		if (&r == table->last_record && r.cursor<4) {
			text[r.cursor] = (show_cursor) ? '.' : ' ';
		}
		nameLabels[i]->setText(text);

		std::ostringstream os;
		os << r.score;
		text = os.str();
		scoreLabels[i]->setText(text);
	}

	Screen::draw();

	SDL_GL_SwapBuffers();
}

