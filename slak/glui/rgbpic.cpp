#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "gl-include.h"
#include "rgbpic.h"

using namespace slak::glui;

RGBPic::RGBPic(std::string fname)
	: x(0), y(0), inited_gfx(false), use_texture(true)
{
	pic = IMG_Load(fname.c_str());
	texw = 1;
	texh = 1;
	while(texw < pic->w) texw *= 2;
	while(texh < pic->h) texh *= 2;

	maxs = (float)(pic->w)/(float)texw;
	maxt = (float)(pic->h)/(float)texh;
}

void slak::glui::sdl2glPixelParams(SDL_PixelFormat * sdlfmt, 
		       unsigned int& format, 
		       unsigned int& type)
{
	if (!sdlfmt->Amask) {
		format = GL_BGR;
		type = GL_UNSIGNED_BYTE;
	} else {
		format = GL_RGBA;
		type = GL_UNSIGNED_BYTE;
	}
}

void RGBPic::draw()
{
	if (!inited_gfx) {
		int gotWidth;
		unsigned int texfmt, fmt, tp;
		sdl2glPixelParams(pic->format, fmt, tp);
		texfmt = (fmt == GL_BGR) ?  GL_RGB : GL_RGBA;

		glTexImage2D(GL_PROXY_TEXTURE_2D,
			     0, texfmt, texw, texh,
			     0, fmt, tp,
			     NULL);
		glGetTexLevelParameteriv(GL_PROXY_TEXTURE_2D,
					 0, GL_TEXTURE_WIDTH,
					 (GLint*)&gotWidth);

		if (gotWidth>0) {
			glGenTextures(1,(GLuint*)&texID);
			glBindTexture(GL_TEXTURE_2D, texID);

			glTexImage2D(GL_TEXTURE_2D,
				     0, texfmt, texw, texh,
				     0, fmt, tp,
				     NULL);

			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, pic->w, pic->h, 
					fmt, tp, pic->pixels);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
					GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, 
					GL_NEAREST);
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		} else 
			use_texture = false;
		inited_gfx = true;
	}

	if (use_texture) {
		glBindTexture(GL_TEXTURE_2D, texID);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);

		glBegin(GL_QUADS);

		glTexCoord2f(0,maxt);
		glVertex2i(x,y); 

		glTexCoord2f(0,0);
		glVertex2i(x,y+pic->h); 

		glTexCoord2f(maxs,0);
		glVertex2i(x+pic->w,y+pic->h); 

		glTexCoord2f(maxs,maxt);
		glVertex2i(x+pic->w,y); 

		glEnd();

		glDisable(GL_TEXTURE_2D);
	} else {
		glRasterPos2i(x,y+pic->h);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glPixelZoom(1, -1);
		glDrawPixels(pic->w, pic->h, GL_BGR, 
			     GL_UNSIGNED_BYTE, 
			     pic->pixels);
	}
}

