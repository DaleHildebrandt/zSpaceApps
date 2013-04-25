//ColorRGB.cpp
//Data defining a single color via values for red, green, and blue
#include "ColorRGB.h"



ColorRGB::ColorRGB(float red, float green, float blue)
{
	this->red = red;
	this->blue = blue;
	this->green = green;
}

float ColorRGB::getRed()
{
	return red;
}
float ColorRGB::getGreen()
{
	return green;
}
float ColorRGB::getBlue()
{
	return blue;
}

ColorRGB::~ColorRGB(void)
{
}
