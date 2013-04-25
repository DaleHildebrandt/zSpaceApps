//VisST.cpp
//Displays the Spatio-Temporal data

#include "VisST.h"
#include <GL\openglut.h>
#include "../Utilities/Parser.hpp"
#include "../OpenGlScene.h"
#include "../Objects/AnnotatedPoint.h"
#include <sstream>
#define PI 3.1459

const float VisST::TIME_AXIS_MAX = 0.3; //Maximum height (Y-axis) we draw to.
const float VisST::LINE_RADIUS = 0.002; //Radius of the cynlinders that connect individual points
const float VisST::POINT_RADIUS = 0.006; //Radius of the spheres that represent each point
const float VisST::TIME_PARTITIONS = 10.0; //How many partitions to display on the backboard
const float VisST::Z_FIGHT_CORR = 0.0001; //Visibly negligible shift to resolve z-fights between two objects with identical z values.
const float VisST::TEXT_SCALE = 1/8000.0f; //Scales the text down to a reasonable size

using namespace zspace::common;

VisST::VisST(float width, float height, std::string texture, DataAccessCSV* data)
{
	plane = new VisPlane(width, height, texture);
	planeHeight = 0.0;
	this->width = width;
	this->height = height;
	this->data = data;
	this->ids = data->getIDs();
	this->text = "HELLO WORLD!";

	//Sets 10 distinct colors to differentiate paths.
	colors.push_back(new ColorRGB(1.0, 0.0, 0.0));
	colors.push_back(new ColorRGB(0.0, 1.0, 0.0));
	colors.push_back(new ColorRGB(0.0, 0.0, 1.0));
	colors.push_back(new ColorRGB(1.0, 1.0, 0.0));
	colors.push_back(new ColorRGB(1.0, 0.0, 1.0));
	colors.push_back(new ColorRGB(0.0, 1.0, 1.0));
	colors.push_back(new ColorRGB(0.5, 0.0, 0.0));
	colors.push_back(new ColorRGB(0.0, 0.5, 0.0));
	colors.push_back(new ColorRGB(0.0, 0.0, 0.5));
	colors.push_back(new ColorRGB(0.5, 0.5, 0.0));
	coord = new Coordinator(width, height);

	vector<AnnotatedPoint> points;
	ColorRGB* currColor;

	//Create a path for each given id
	for(int i = 0; i < ids.size(); i++)
	{
		cout << "Id at " << i << ": " << ids[i] << endl;
		currColor = colors[i];
		points = data->getDisplayPath(ids[i]);
		paths.push_back(new VisPath(points,POINT_RADIUS,LINE_RADIUS,*currColor));
	}
	selectedPathId = 0; //The path housing the currently selected point
	rotation = 0; //Angle of rotation of the scene
	
	//Generating hitboxes for items on the legend
	for(int i = 0; i < ids.size(); i++){
		AxisAlignedBox currBox = AxisAlignedBox(width*0.8, TIME_AXIS_MAX*((9.0-i)/TIME_PARTITIONS), -height, width, TIME_AXIS_MAX*((9.0-i+1)/TIME_PARTITIONS), -height);
		legendHitboxes.push_back(currBox);
	}

	//Generate hitbox for ground
	groundHitbox = AxisAlignedBox(0, 0, -height, width, 0, 0);

	selectedItem = 0; //Item on the legend that is currently selected

	groundIntersection = false;
	pointIntersection = false;
	legendIntersection = false;

	highlightGround = false;
}

//destructor
VisST::~VisST(void)
{
	delete coord;
	delete polyLine;
	delete data;
	for(int i = 0; i < colors.size(); i++){
		delete colors[i];
	}
	colors.clear();

	for(int i = 0; i < paths.size(); i++){
		delete paths[i];
	}
	paths.clear();
}

//Tests for intersection between stylus ray and interactable objects in the scene (points & legend)
std::pair<bool, float> VisST::testIntersection(Ray ray, float stylusLength)
{
	groundIntersection = false;
	legendIntersection = false;
	pointIntersection = false;

	//Get original Ray origin and direction
	Vector3 rayOrigin = ray.getOrigin();
	Vector3 rayDirection = ray.getDirection();
	
	//Untransform stylus ray (origin and direction) in order to perform a proper hit test.
	//Undo rotation transformation (multiply origin & direction by inverse [which is also the transpose in this case] 3x3 rotation matrix
	float angleRads = rotation*(PI/180.0f);
	ray.setOrigin(Vector3(rayOrigin.x*cos(angleRads) - rayOrigin.z*sin(angleRads), rayOrigin.y, rayOrigin.x*sin(angleRads) + rayOrigin.z*cos(angleRads)));
	ray.setDirection(Vector3(rayDirection.x*cos(angleRads) - rayDirection.z*sin(angleRads), rayDirection.y, rayDirection.x*sin(angleRads) + rayDirection.z*cos(angleRads)));
	//Undo translation transformation (translate origin in opposite direction)
	rayOrigin = ray.getOrigin();
	ray.setOrigin(Vector3(rayOrigin.x +(plane->getWidth()/2.0), rayOrigin.y, rayOrigin.z - (plane->getHeight()/2.0)));

	//Test for interaction with the ground
	highlightGround = false;
	std::pair<bool, float> groundResult;
	std::pair<bool,float> result;
	result.first = false;
	result.second = 0.0;
	groundResult = ray.intersects(groundHitbox);

	if(groundResult.first && (!result.first || (result.first && groundResult.second < result.second)) && groundResult.second < stylusLength){
		result = groundResult;
		groundIntersection = true;
		legendIntersection = false;
		pointIntersection = false;
	}

	//Tests for intersection with an item on the legend
	std::pair<bool, float> legendResult;

	selectedItem = -1;
	for(int i = 0; i < legendHitboxes.size(); i++)
	{
		legendResult = ray.intersects(legendHitboxes[i]);
		if(legendResult.first && (!result.first || (result.first && legendResult.second < result.second)) && legendResult.second < stylusLength){
			groundIntersection = false;
			legendIntersection = true;
			pointIntersection = false;
			result = legendResult;
			selectedItem = i;

		}
	}
	legendResult = result;

	//Tests for intersection with a point
	std::pair<bool,float> pathResult;

	for(int i = 0; i < paths.size(); i++)
	{
		pathResult = paths[i]->testIntersection(ray);
		if(pathResult.first && (!result.first || (result.first && pathResult.second < result.second)) && pathResult.second < stylusLength){
			groundIntersection = false;
			legendIntersection = false;
			pointIntersection = true;
			result = pathResult;
			selectedPathId = i;
		}
	}
	pathResult = result;

	//If closest intersection with ray is a point
	if(pointIntersection){
		//cout << "Point Intersection" << endl;
		paths[selectedPathId]->select();
		selectedItem = -1;
		result = pathResult;
	}
	//If closest intersection with ray is an item on the legend
	else if(legendIntersection){
		//cout << "Legend Intersection " << endl;
		result = legendResult;
	}
	//If closest intersection with ray is the ground plane
	else if(groundIntersection){
		//cout << "Ground Intersection " << endl;
		selectedItem = -1;
		highlightGround = true;
	}
	//No intersection
	else{
		selectedItem = -1;
	}

	return result;
}

//Sets the height of the plane to match the laser pointer's height
//The heights snap to ones that are labelled on the backboard.
void VisST::setPlane(Vector3 point)
{
	int i = 0;
	for( i = 0; point.y > 0 && point.y > TIME_AXIS_MAX*(i/TIME_PARTITIONS) && i < TIME_PARTITIONS; i++){
	}
	planeHeight = (TIME_AXIS_MAX*(i/TIME_PARTITIONS)) + 0.0001;
}

//Sets the rotation of the scene
void VisST::setRotation(float degrees)
{
	rotation = degrees;
}

//Handles when an item is selected (hover) 
// and the circluar stylus button is pressed.
void VisST::confirmSelection()
{
	//Point selection confirmation
	paths[selectedPathId]->confirmSelection();

	//Legend item selection confirmation
	if(selectedItem >= 0 && selectedItem < paths.size()){
		paths[selectedItem]->toggleVisibility();
	}

	//Ground selection confirmation (not in use currently)
	if(highlightGround){

	}
}

//Draws the Spatio-temporal visualization
void VisST::render(void)
{

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix(); // Save pre-VisST modelview matrix
	glRotatef((GLfloat)rotation, (GLfloat)0.0, (GLfloat)1.0, (GLfloat)0.0);
	glTranslatef(-(plane->getWidth()/2.0), 0.0, (plane->getHeight()/2.0));//Center VisPlane on origin
	//Highlights ground if pointed at
	/*if(highlightGround)
		plane->setColor(0.0, 1.0, 0.0);
	else
		plane->setColor(1.0, 1.0, 1.0);*/

	plane->render(); //Draw the ground plane displaying the map

	glColor3f(1.0, 0.0, 0.0);
	glLineWidth(20);
	vector<Point3D> points;
	ColorRGB* currColor;

	for(int i = 0; i <paths.size(); i++) {
		paths[i]->render();
	}

	renderBackboard();

		//Renders the height selection plane
		//glPushMatrix();
		//glTranslatef(0, planeHeight, 0);

		////Set transparency
		//glColor4f(0.0f, 0.0f, 1.0f, 0.2f);
		//glEnable (GL_BLEND); 
		//glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		////plane->render();
		////glBegin(GL_QUADS);
		////	glTexCoord2d(0.0, 0.0);glVertex3f(0.0, 0.0, 0.0);
		////	glTexCoord2d(1.0, 0.0);glVertex3f(width, 0.0, 0.0);
		////	glTexCoord2d(1.0, 1.0);glVertex3f(width, 0.0, -height);
		////	glTexCoord2d(0.0, 1.0);glVertex3f(0.0, 0.0, -height);		
		////glEnd(); 
		//glDisable(GL_BLEND);
		//glPopMatrix();

	glPopMatrix(); //Restore pre-VisST modelview matrix
}

//Renders the backboard of the STV, showing time divisions,
//and an interactable legend with entries for each id/path.
void VisST::renderBackboard()
{
	double date; 
	string str;
	//Draw for each division
	for(int i = 0; i < TIME_PARTITIONS; i++){

		date = coord->getMeasuringUnits(1, TIME_PARTITIONS, (TIME_PARTITIONS-i));

		str = Parser::date2String(date);

		//Drawing the lines across time axis
		glPushMatrix();
		glTranslatef(0,  TIME_AXIS_MAX*(i/TIME_PARTITIONS), -height);
		renderBackboardLine();
		renderBackboardLabel(str);

		
		if(9-i < ids.size()){
			glColor3f(colors[9-i]->getRed(), colors[9-i]->getGreen(), colors[9-i]->getBlue());
			std::ostringstream ss;
			ss << "Bus " << (Parser::int2String(ids[9-i])) << endl;
			//glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char*) ss.str().c_str());
			renderBackboardLegend(ss.str());
		}
		
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix();
		//Draw hitboxes for legend
			if(9-i < ids.size() && 9-i == selectedItem){
				glTranslatef(0.0, 0.0, -Z_FIGHT_CORR);
				glColor3f(1.0, 0.0, 0.0);
				glBegin(GL_QUADS);
					glVertex3f(width*0.8, TIME_AXIS_MAX*(i/TIME_PARTITIONS), -height);
					glVertex3f(width*0.8, TIME_AXIS_MAX*((i+1)/TIME_PARTITIONS), -height);
					glVertex3f(width, TIME_AXIS_MAX*((i+1)/TIME_PARTITIONS), -height);
					glVertex3f(width, TIME_AXIS_MAX*(i/TIME_PARTITIONS), -height);
				glEnd();
			}
		glPopMatrix();

	}
}

void VisST::renderBackboardLine()
{
	glLineWidth(1);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);
		//glVertex3f(0, 0.3*(i/10.0), -height);
		//glVertex3f(width, 0.3*(i/10.0), -height);

		glVertex3f(0, 0, 0);
		glVertex3f(width, 0, 0);
	glEnd();
}

void VisST::renderBackboardLabel(string str)
{
	//Draw time labels
		glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef(0, 0.001, 0.0);
		glScalef(1/8000.0f, 1/8000.0f, 1/8000.0f);
		//glRotatef((GLfloat)-OpenGlScene::getRotation(),(GLfloat) 0,(GLfloat) 1,(GLfloat) 0);
			glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char*) str.c_str());
		glPopMatrix();

}

void VisST::renderBackboardLegend(string str)
{

		//Draw Legend Colors
		glPushMatrix();
			glTranslatef(width *(0.8), 0.001, 0.0);
				glBegin(GL_QUADS);
					glVertex3f(0.0,0.0,0.0);
					glVertex3f(width*(0.05), 0.0, 0.0);
					glVertex3f(width*(0.05), TIME_AXIS_MAX*(1/TIME_PARTITIONS), 0.0);
					glVertex3f(0.0, TIME_AXIS_MAX*(1/TIME_PARTITIONS), 0.0);
				glEnd();
		glPopMatrix();

		//Draw legend text
		glColor3f(1.0, 1.0, 1.0);
		glPushMatrix();
			//glTranslatef(width, 0.0, 0.0);
			glTranslatef(width *(0.85), 0.001, 0.0);
			glScalef(TEXT_SCALE, TEXT_SCALE, TEXT_SCALE);
				glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char*) str.c_str());
		glPopMatrix();


}