//VisPlane.cpp
//Draws a textured rectangle onto the screen, given a width (x-axis) and height (negative z-axis)
#include "VisPlane.h"
#include <SOIL.h>
#include <gl/GL.h>
#include <gl/GLU.h>

//constructor
VisPlane::VisPlane(double width, double height, string texture)
{
	this->width = width;
	this->height = height;
	this->texture = SOIL_load_OGL_texture( //Loads texture using SOIL
		texture.c_str(),
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
	);
	this->color = new ColorRGB(1.0, 1.0, 1.0);
}
//destructor
VisPlane::~VisPlane(void)
{
	delete color;
}

//Mutators
void VisPlane::setColor(float red, float green, float blue)
{
	color = new ColorRGB(red, green, blue);
}

//Accessors
double VisPlane::getHeight() //get z-wise distance of plane
{
	return height;
}

double VisPlane::getWidth() //get x-wise distance of plane
{
	return width;
}

//Drawing
void VisPlane::render()
{
	//Set up the VisPlane's texture for drawing
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix(); // Save pre-VisPlane modelview matrix
	glColor3f(color->getRed(), color->getGreen(), color->getBlue());

	//Draws the textured VisPlane
	glBegin(GL_QUADS);
		glTexCoord2d(0.0, 0.0);glVertex3f(0.0, 0.0, 0.0);
		glTexCoord2d(1.0, 0.0);glVertex3f(width, 0.0, 0.0);
		glTexCoord2d(1.0, 1.0);glVertex3f(width, 0.0, -height);
		glTexCoord2d(0.0, 1.0);glVertex3f(0.0, 0.0, -height);		
	glEnd(); 

	glPopMatrix(); //restore pre-VisPlane modelview matrix

	glDisable(GL_TEXTURE_2D); //Avoids applying texture to other drawn objects
}