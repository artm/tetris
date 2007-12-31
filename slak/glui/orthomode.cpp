#include "gl-include.h"
#include "app.h"
#include "orthomode.h"

using namespace slak::glui;

void OrthoMode::drawPre() 
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,App::getScreenWidth(),
		0,App::getScreenHeight(),-1,1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void OrthoMode::drawPost() 
{
}
