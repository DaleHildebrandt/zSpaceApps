#pragma once
#include "../MathHelper/MathHelper.hpp"
using namespace MHTypes;
using namespace std;
class AnnotatedPoint
{
public:
	AnnotatedPoint(Point3D point, string text);
	~AnnotatedPoint(void);
	Point3D AnnotatedPoint::getPoint();
	string AnnotatedPoint::getText();
private:
	Point3D point;
	string text;
};

