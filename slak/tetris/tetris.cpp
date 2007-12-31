#include <cstring>
#include <algorithm>
#include "tetris.h"
#include "tetris_app.h"

using namespace slak::tetris;


const int Game::score_for_clear[] =
{ 40, 100, 300, 1200 };

Game::Game() : 
	ticks_per_fast_fall(1),
	ticks_per_strobe_fx(30),
	field(10,16), 
	sm(NULL),
	state(INIT_STATE),
	hi_scores(10)
{}

void Game::dropNextTetrad()
{
  // try to drop a block
	if (field.drop(nextTetrad)) {
	        // reset can fast fall
		can_fast_fall = true;
		// prepare next block
		nextTetrad = Tetrad::make(); 
	} else 
	  // if it's not possible - game over
		enter(GAME_OVER_STATE);
}

void Game::tick()
{

	switch(state) {
	case NORMAL_STATE:
		normalTick();
		break;
	case FAST_FALL_STATE:
		fastFallTick();
		break;
	case STROBE_FX_STATE:
		strobeTick();
		break;
	}
}

void Game::strobeTick()
{
	fall_ticks -- ;
	if (fall_ticks <= 0)  {
		int clear = field.delAllComplete();
		score += score_for_clear[clear-1] * (level+1);
		cleared += clear;
		setLevel(cleared / 10);
		enter(NORMAL_STATE);
		dropNextTetrad();

	}
}

void Game::normalTick()
{
	fall_ticks -- ;
	if (fall_ticks<=0) {
		if (sm) sm->play("click");
		fall_ticks = ticks_per_normal_fall;
		if (!field.moveFalling(0,-1)) {
			field.renderFalling();
			if (field.countComplete() > 0) {
				if (sm) sm->play("tada");
				enter(STROBE_FX_STATE);
			} else {
				if (sm) sm->play("snap");
				dropNextTetrad();
			}
		}
	}
}

void Game::fastFallTick()
{
	fall_ticks -- ;
	if (fall_ticks<=0) {
		if (!field.moveFalling(0,-1)) 
			enter(NORMAL_STATE);
		else
			fall_ticks = ticks_per_fast_fall;
	}
}

void Game::newGame()
{
	score = 0;
	cleared = 0;
	setLevel(0);
	field.clear();
	nextTetrad = Tetrad::make();
	dropNextTetrad();
	enter(NORMAL_STATE);
}

void Game::enter(game_state st)
{
        // don't bother if already in that state
	if (state == st)
		return;
	
	// requested the impossible
	if (st == FAST_FALL_STATE && !can_fast_fall) return;

	state = st;
	// push state changed event for the application object 
	// to react on...
	slak::glui::App::push(TetrisApp::STATE_CHANGED,NULL,NULL);

	// ...but prepare what we know ourselves
	switch(st) {
	case NORMAL_STATE:
		fall_ticks = ticks_per_normal_fall;
		break;
	case FAST_FALL_STATE:
	        // when falling - can't ask as to drop even more
		can_fast_fall = false;
		// ask sound manager to woosh
		if (sm) sm->play("woosh");
		// dropping causes score increase!
		score += field.y * (level+1);
		fall_ticks = ticks_per_fast_fall;
		break;
	case STROBE_FX_STATE:
		fall_ticks = ticks_per_strobe_fx;
		break;
	case GAME_OVER_STATE:
		hi_scores.insertRecord(score);
		break;
	}
}

void Game::setLevel(int level)
{
	this->level = level;
	ticks_per_normal_fall =  48 - 2*level;
}

