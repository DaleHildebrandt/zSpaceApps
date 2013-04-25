#pragma once
#ifndef VISPLANE_H
#define VISPLANE_H
#include <iostream>
#include <Windows.h>
#include <GL\GLU.h>
#include "../Objects/ColorRGB.h"

using namespace std;

class VisPlane
{
public:
	VisPlane(double width, double height, std::string texture);
	~VisPlane(void);
	void render();
	double getHeight();
	double getWidth();
	void setColor(float red, float green, float blue);
private:
	double width; //length along the x-axis
	double height; //length along the z-axis
	GLuint texture; //texture to be applied to the VisPlane
	ColorRGB* color;
};

#endif