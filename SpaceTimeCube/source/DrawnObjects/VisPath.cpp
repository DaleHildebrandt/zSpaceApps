//VisPath.cpp
//Represents a path for a single id
//Contains the Points of the path, and also the lines connecting the points.
#include "VisPath.h"
#include <GL\GL.h>

//Constructor
VisPath::VisPath(vector<AnnotatedPoint> points, double pointRadius, double lineRadius, ColorRGB color)
{
	for(int i = 0; i < points.size(); i++)
	{
		this->points.push_back(new VisSphere(points[i].getPoint(), points[i].getText(), pointRadius, color));
	}
	this->polyLine = new VisPolyLine(points, lineRadius);
	this->color = new ColorRGB(color.getRed(), color.getGreen(), color.getBlue());
	selected = false;
	selectedPointId = -1;
	visible = true;
}

//destructor
VisPath::~VisPath(void)
{
	delete color;
	delete polyLine;
	for(int i = 0; i < points.size(); i++)
	{
		delete points[i];
	}
	points.clear();
}

//Tests whether the stylus laser beam is intersecting something
//(either data points or items on the legend)
std::pair<bool,float> VisPath::testIntersection(Ray ray)
{
	std::pair<bool, float> result;
	std::pair<bool,float> pathResult;
	result.first = false;
	result.second = 0.0;

	deselect();
	//Only test for intersections if the path is visible
	if(visible){
		//Test all points in the path for intersections
		//Mark only the point of intersection that is closest to the stylus
		//(in the case that multiple intersections occur)
		for(int i = 0; i < points.size(); i++)
		{
			pathResult = points[i]->testIntersection(ray);
			if(pathResult.first && (!result.first || (result.first && pathResult.second < result.second))){
				result = pathResult;
				selectedPointId = i;
			}
		}
	}
	
	return result;
}

//Toggles on or off whether user can see & interact with the path
void VisPath::toggleVisibility()
{
	visible = !visible;
}

//Perform a selection of a point on the path
void VisPath::select()
{
	selected = true;
	points[selectedPointId]->select();
}

//Deselect the path
void VisPath::deselect()
{
	selected = false;
}

//Locks in a selection
void VisPath::confirmSelection()
{
	if(selectedPointId > -1)
		points[selectedPointId]->confirmSelection();
}

//Draws the path to the screen
void VisPath::render()
{
	if(visible){
		glPushMatrix();
		glColor3f(color->getRed(), color->getGreen(), color->getBlue());
		//Draw connecting cylinders between the points along the path
		polyLine->render();
		//Draw the points along the path
		for(int i = 0; i < points.size(); i++){
			points[i]->render();
		}
		glPopMatrix();
	}
}