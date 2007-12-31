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
#include <cstdlib>
#include <cstring>

#include "tetrad.h"

using namespace slak::tetris;

Tetrad::Tetrad()
	: width(0), height(0), mask(NULL)
{
}

Tetrad::Tetrad(int w, int h, int cx, int cy)
	: width(w), height(h)
{
	mask = new square_state[w*h];
	// use or find center
	this->cx = (cx >= 0) ? cx : w/2;
	this->cy = (cy >= 0) ? cy : h/2;
	clear();
}

Tetrad::Tetrad(const Tetrad& other)
	: width(other.width),
	  height(other.height),
	  cx(other.cx), cy(other.cy)
{
	mask = new square_state[width*height];
	memcpy(mask,other.mask,width*height*sizeof(square_state));
}

Tetrad& Tetrad::operator=(const Tetrad& other)
{
	width = other.width;
	height = other.height;
	cx = other.cx;
	cy = other.cy;
	if (other.mask) {
		mask = new square_state[width*height];
		memcpy(mask,other.mask,width*height*sizeof(square_state));
	} else
		mask = NULL;
	return *this;
}

Tetrad::~Tetrad()
{
	if (mask) delete mask;
}

square_state& Tetrad::sq(int i, int j)
{
	assert(mask != NULL);
	assert(i<width);
	assert(j<height);
	return mask[i + j*width];
}

square_state Tetrad::sq(int i, int j) const
{
	assert(mask != NULL);
	assert(i<width);
	assert(j<height);
	return mask[i + j*width];
}

Tetrad Tetrad::rotate() const
{

	assert(mask);

	// find new center
	int w = height,
	    h = width,
	    ncx = height - cy - 1,
	    ncy = cx;
	// allocate new tetrad
	Tetrad rotated(w,h,ncx,ncy);

	// and copy the mask
	for(int i = 0; i < w; i++)
		for(int j = 0; j < h; j++)
			rotated.sq(i,j) = sq(j,w-i-1);
	// return new tetrad
	return rotated;
}

Tetrad Tetrad::make(shape s, int n_rot)
{
	Tetrad f;

	if (s == RANDOM_SHAPE)
		s = (shape)(rand() % N_SHAPES);

	switch(s) {
	case O:
		f = Tetrad(2,2);
		f.sq(0,0) = BLUE;
		f.sq(0,1) = BLUE;
		f.sq(1,0) = BLUE;
		f.sq(1,1) = BLUE;
		break;
	case I:
		f = Tetrad(4,1);
		f.sq(0,0) = RED;
		f.sq(1,0) = RED;
		f.sq(2,0) = RED;
		f.sq(3,0) = RED;
		break;
	case L:
		f = Tetrad(2,3);
		f.sq(0,2) = MAGENTA;
		f.sq(0,1) = MAGENTA;
		f.sq(0,0) = MAGENTA;
		f.sq(1,0) = MAGENTA;
		break;
	case J:
		f = Tetrad(2,3);
		f.sq(1,2) = BLACK;
		f.sq(1,1) = BLACK;
		f.sq(0,0) = BLACK;
		f.sq(1,0) = BLACK;
		break;
	case Z:
		f = Tetrad(2,3);
		f.sq(0,2) = CYAN;
		f.sq(0,1) = CYAN;
		f.sq(1,1) = CYAN;
		f.sq(1,0) = CYAN;
		break;
	case S:
		f = Tetrad(2,3);
		f.sq(1,2) = GREEN;
		f.sq(0,1) = GREEN;
		f.sq(1,1) = GREEN;
		f.sq(0,0) = GREEN;
		break;
	case T:
		f = Tetrad(3,2,1,1);
		f.sq(1,0) = BROWN;
		f.sq(0,1) = BROWN;
		f.sq(1,1) = BROWN;
		f.sq(2,1) = BROWN;
		break;
	default:
		throw "Bad shape";
	}

	if (n_rot < 0)
		n_rot = rand()%4;
	for(int i=0; i<n_rot; i++)
		f = f.rotate();

	return f;
}

bool Tetrad::collides(int x, int y,const Tetrad& other)
{
	assert(mask);
	assert(other.mask);

	if (x<0 || y<0 || x+other.width > width || y+other.height > height)
		return true;

	for(int i=0; i<other.width; i++)
		for(int j=0; j<other.height; j++)
			if (other.sq(i,j) != EMPTY &&
			    sq(x+i,y+j) != EMPTY)
				return true;
	return false;
}

bool Tetrad::operator==(const Tetrad& other) const
{
	if (width != other.width || height != other.height)
		return false;
	if (mask && !other.mask || !mask && other.mask)
		return false;
	for(int i=0; i<width*height; i++)
		if (mask[i] != other.mask[i])
			return false;
	return true;
}

bool Tetrad::operator!=(const Tetrad& other) const
{
	return ! ((*this) == other);
}

void Tetrad::clear()
{
	assert(mask);
	memset(mask,0,sizeof(square_state)*width*height);
}

bool Tetrad::lineComplete(int j) const
{
	for(int i = 0; i<width; i++)
		if (sq(i,j)==EMPTY)
			return false;
	return true;
}

void Tetrad::delLine(int j)
{
	int i0 = j*width;
	int i1 = (j+1)*width;
	memmove(mask+i0,mask+i1,(height-j-1)*width*sizeof(square_state));
	memset(mask+(height-1)*width,0,width*sizeof(square_state));
}

int Tetrad::delAllComplete()
{
	int count = 0;
	for(int j=0; j<height; j++)
		while (lineComplete(j)) {
			delLine(j);
			count++;
		}
	return count;
}

int Tetrad::countComplete()
{
	int count = 0;
	for(int j=0; j<height; j++)
		if (lineComplete(j)) {
			count++;
		}
	return count;
}

