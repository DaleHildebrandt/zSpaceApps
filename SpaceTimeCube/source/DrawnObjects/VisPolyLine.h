#pragma once

#include "../MathHelper/MathHelper.hpp"
#include <vector>
#include "../Objects/AnnotatedPoint.h"

using namespace MHTypes;
using namespace std;
class VisPolyLine
{
public:
	VisPolyLine(vector<AnnotatedPoint> points, double radius);
	~VisPolyLine(void);
	void render(void);
private:
	vector<Point3D> points;
	double radius;
};

