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

#include <assert.h>
#include "field.h"

using namespace slak::tetris;

Field::Field(int w, int h) : Tetrad(w,h), falling()
{
}

bool Field::drop(const Tetrad& f)
{
	int nx, ny;

	// if there was a block falling - render it into the field
	if (!falling.empty())
		renderFalling();

	// find where to start
	ny = height - f.height;
	nx = (width-f.width)/2;

	// and actually place the block there.
	// even if we'll return false (collision)
	// we have to place the block so it'll be
	// drawn.
	falling = f;
	x = nx;
	y = ny;

	// return if it hasn't collided
	return !collides(x,y,falling);
}

void Field::renderFalling()
{
  // copy square colours to the field
	for(int i=0; i<falling.width; i++)
		for(int j=0; j<falling.height; j++)
			if (falling.sq(i,j) != EMPTY)
				Tetrad::sq(x+i,y+j) = falling.sq(i,j);
  // reset falling to empty tetrad
	falling = Tetrad();
}

// if at all possible - move the falling
bool Field::moveFalling(int dx, int dy)
{
	assert(!falling.empty());

	int nx = x+dx, ny = y+dy;
	if (collides(nx,ny,falling))
		return false;

	x = nx;
	y = ny;

	return true;
}

square_state Field::sq(int i, int j) const
{
	assert(i<width);
	assert(j<height);

	// if the square is empty in or is outside the falling tetrad...
	if (falling.empty()
	    || (i < x) || (i >= x+falling.width)
	    || (j < y) || (j >= y+falling.height)
	    || (falling.sq(i-x,j-y) == EMPTY))
	  // return its colour in the field
		return Tetrad::sq(i,j);
	else
	  // otherswise - it's colour in the tetrad
		return falling.sq(i-x,j-y);
}

bool Field::rotateFalling()
{
  // rotating is easy:
	Tetrad rot = falling.rotate();
  // but now we have to find the new coordinates of the falling
	// recenter
	int cx = x + falling.cx,
	    cy = y + falling.cy;
	int nx = cx - rot.cx,
	    ny = cy - rot.cy;
  // if at Field top - re-fit vertically
	if (ny+rot.height > height)
		ny = height-rot.height;
  // ... and check if the new orientation is at all possible
	if (collides(nx,ny,rot))
		return false;
  // update if it is
	falling = rot;
	x = nx;
	y = ny;
	return true;
}

void Field::clear()
{
	Tetrad::clear();
	falling = Tetrad();
}

