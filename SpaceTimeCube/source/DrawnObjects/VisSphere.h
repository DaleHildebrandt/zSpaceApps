#pragma once
#include "../MathHelper\MathHelper.hpp"
#include <ZSpace\Common\Math\Sphere.h>
#include <ZSpace\Common\Math\Ray.h>
#include "../Objects/ColorRGB.h"

using namespace MHTypes;
using namespace zspace::common;

class VisSphere
{
public:
	VisSphere(Point3D pos, std::string text, double radius, ColorRGB color);
	~VisSphere(void);
	Sphere getSphere();
	std::pair<bool,float> VisSphere::testIntersection(Ray ray);
	void render();
	void select();
	void deselect();
	void confirmSelection();

private:
	Sphere sphere; //Handles hit-testing of sphere with stylus ray
	bool selected; //Point is being hovered over by the laser
	ColorRGB* color; // colo or sphere
	Point3D pos; //position of sphere
	std::string text; //Annotation associated with sphere
	double radius; //display radius of sphere
	double origRadius; //original radius of sphere on creation
	bool selectionConfirmed; //Point has been selected by the laser
	//The ratio bewtween the hit-test and the original display size (ie. hit-test size is SNAPPING_RATIO times larger than original display size)
	static const float SNAPPING_RATIO;
	static const float TEXT_Y_OFFSET;
	static const float TEXT_SCALE;
};

