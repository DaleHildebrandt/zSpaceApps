#pragma once
#include "VisPlane.h"
#include "VisPolyLine.h"
#include "VisPath.h"
#include "../DataAccess\DataAccessCSV.hpp"
#include "../MathHelper\MathHelper.hpp"
#include "../Objects/ColorRGB.h"
#include "../Utilities/Coordinator.hpp"
#include <ZSpace\Common\Math\Ray.h>
#include <vector>
using namespace MHTypes;
using namespace zspace::common;
class VisST
{
public:
	VisST(float width, float height, std::string texture, DataAccessCSV* data);
	void render(void);
	~VisST(void);
	std::pair<bool, float> testIntersection(Ray ray, float stylusLength);
	void confirmSelection();
	void setPlane(Vector3 point);
	void setRotation(float degrees);

private:
	double width;
	double height;
	VisPlane* plane;
	VisPolyLine* polyLine;
	DataAccessCSV* data;
	Coordinator* coord;
	vector<int> ids;
	vector<ColorRGB*> colors;
	string text;
	int selectedPathId;
	float planeHeight;
	float rotation;
	const static float POINT_RADIUS;
	const static float LINE_RADIUS;
	const static float TIME_AXIS_MAX;
	const static float TIME_PARTITIONS;
	const static float Z_FIGHT_CORR;
	const static float TEXT_SCALE;

	bool pointIntersection;
	bool legendIntersection;
	bool groundIntersection;
	bool highlightGround;

	vector<AxisAlignedBox> legendHitboxes;
	AxisAlignedBox groundHitbox;
	int selectedItem;

	vector<VisPath*> paths;

	void renderBackboard();
	void renderBackboardLine();
	void renderBackboardLabel(string str);
	void renderBackboardLegend(string str);

};

