//AnnotatedPoint.cpp
//Houses info needed to visually represent a data point.
//Includes the 3D position of the point, as well as
//an associated annotation.
#include "AnnotatedPoint.h"

//constructor
AnnotatedPoint::AnnotatedPoint(Point3D point, string text)
{
	this->point = point;
	this->text = text;
}

//destructor
AnnotatedPoint::~AnnotatedPoint(void)
{
}

//Accessors
Point3D AnnotatedPoint::getPoint()
{
	return point;
}

string AnnotatedPoint::getText()
{
	return text;
}