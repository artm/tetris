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

#include <SDL.h>
#include <SDL_ttf.h>
#include "slak/glui/gl-include.h"
#include "tetris_screen.h"
#include "tetris_app.h"
#include "slak/glui/orthomode.h"
#include "slak/glui/rgbpic.h"

using namespace slak::tetris;
using namespace slak::glui;

// private data
struct slak::tetris::GameScreenPriv {
	SDL_TimerID game_over_timer;
	GameScreenPriv() : game_over_timer(0) {}
};

GameScreen::GameScreen(Game * game)
	: game(game), renderer(game), priv(new GameScreenPriv())
{
  // add overlays
	overlays.push_back(new RGBPic("media/bitmaps/tetris-main.bmp"));
	overlays.push_back(&renderer);
	RGBPic * gameover = new RGBPic("media/bitmaps/game-over.png");
	gameover->x = App::getScreenWidth()/2 - gameover->pic->w/2;
	gameover->y = App::getScreenHeight()/2 - gameover->pic->h/2;
	gameover_toggle.kid = gameover;
	gameover_toggle.on = false;
	overlays.push_back(&gameover_toggle);
  // and a draw mode
	modes.push_back(new OrthoMode);
}

GameScreen::~GameScreen()
{
	delete priv;
}

bool GameScreen::handle(SDL_Event& ev)
{
	switch(ev.type) {
	// handle keys
	case SDL_KEYDOWN:
		switch (game->state) {
		case NORMAL_STATE:
		case FAST_FALL_STATE:
			switch(ev.key.keysym.sym) {
			case SDLK_ESCAPE:
				App::push(TetrisApp::GOTO_ROOT);
				break;
			case SDLK_RIGHT:
				game->right();
				break;
			case SDLK_LEFT:
				game->left();
				break;
			case SDLK_UP:
				game->rotate();
				break;
			case SDLK_DOWN:
				game->enter(FAST_FALL_STATE);
				break;
			}
			return true;
		case GAME_OVER_STATE:
			// any key in gameover state
			if (priv->game_over_timer) {
				SDL_RemoveTimer(priv->game_over_timer);
				priv->game_over_timer = 0;
			}
			App::push(TetrisApp::GOTO_HISCORES,NULL,NULL);
			return true;
		}
		break;
	// and custom events
	case SDL_USEREVENT:
		switch(ev.user.code) {
		case TetrisApp::TICK:
			game->tick();
			return true;
		case TetrisApp::STATE_CHANGED:
			if (game->state == GAME_OVER_STATE) {
				priv->game_over_timer =
					App::push(TetrisApp::GOTO_HISCORES,NULL,NULL,4000);
				gameover_toggle.on = true;
			} else {
				gameover_toggle.on = false;
			}
			return true;
		}
		break;
	}
	// or pass event to the parent class
	return Screen::handle(ev);
}

void GameScreen::draw()
{
	Screen::draw();
	// for greater flexibility default draw() doesn't swap buffers - do it here
	SDL_GL_SwapBuffers();
	// this happens often - candidate for refactoring...
}


