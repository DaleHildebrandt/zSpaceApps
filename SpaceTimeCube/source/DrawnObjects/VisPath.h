#pragma once
#include "VisPolyLine.h"
#include "VisSphere.h"
#include "../Objects/ColorRGB.h"
#include "../MathHelper/MathHelper.hpp"
#include <vector>
#include <ZSpace\Common\Math\Ray.h>
#include "../Objects/AnnotatedPoint.h"

using namespace zspace::common;
using namespace MHTypes;
using namespace std;
class VisPath
{
public:
	VisPath(vector<AnnotatedPoint> points, double pointRadius, double lineRadius, ColorRGB color);
	~VisPath(void);
	void render();
	std::pair<bool,float> VisPath::testIntersection(Ray ray);
	void select();
	void deselect();
	void confirmSelection();
	void toggleVisibility();

private:
	vector<VisSphere*> points;
	VisPolyLine* polyLine;
	ColorRGB* color;
	int selectedPointId;
	bool selected;
	bool visible;
};

