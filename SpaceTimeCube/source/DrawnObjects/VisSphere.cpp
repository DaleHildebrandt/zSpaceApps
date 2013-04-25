//VisSphere.cpp
//Represents a sphereical object that can be drawn to the screen with associated text.
#include "VisSphere.h"
#include <GL\openglut.h>
#include "../OpenGlScene.h"

float const VisSphere::SNAPPING_RATIO = 1.8;   // Line1
float const VisSphere::TEXT_Y_OFFSET = 0.0095;
float const VisSphere::TEXT_SCALE = 1/20000.0f;

using namespace zspace::common;

//constructor
VisSphere::VisSphere(Point3D pos, std::string text, double radius, ColorRGB color)
{
	sphere = Sphere(Vector3(pos.x,pos.y,pos.z), SNAPPING_RATIO*radius); //create hitbox

	this->color =  new ColorRGB(color.getRed(), color.getBlue(), color.getGreen());
	this->pos = pos;
	this->radius = radius;
	this->origRadius = radius;
	this->text = text;

	selected = false; //Not yet selected
	selectionConfirmed = false;
}

//destructor
VisSphere::~VisSphere(void)
{
}

//Gets the sphere's hitbox, for intersection testing
Sphere VisSphere::getSphere()
{
	return sphere;
}

//Tests whether sphere is intersected by the given ray

std::pair<bool,float> VisSphere::testIntersection(Ray ray)
{
	deselect();
	return ray.intersects(sphere);
}

//Selects the Sphere (ie. user has hovered over sphere)
void VisSphere::select()
{
	selected = true;
	radius = sphere.getRadius();
}
//Deselects the sphere
void VisSphere::deselect()
{	
	if(!selectionConfirmed)
		selected = false;
	radius = origRadius;
}
//Confirms selection. (ie. user has hovered & clicked)
void VisSphere::confirmSelection()
{
	selectionConfirmed = !selectionConfirmed;
}

//Draws the Sphere to the Screen!
void VisSphere::render()
{
	//Highlight sphere if selected
	if(selected)
		glColor3f(1.0, 0.65, 0.0);
	else
		glColor3f(color->getRed(), color->getBlue(), color->getGreen());

	glPushMatrix(); //Save pre-sphere Modelview matrix
	//Position at correct location on map
			glTranslatef(pos.x, pos.y, pos.z);
				
				//Draw the sphere
				GLUquadricObj *quadric=gluNewQuadric();
				gluQuadricNormals(quadric, GLU_SMOOTH);
				gluSphere(quadric, radius, 36, 18);
				gluDeleteQuadric(quadric);

				//Display text if selected
				if(selected){
					glDisable(GL_LIGHTING); //Ensures text is a bright white, and not made darker due to lighting effects
					glLineWidth(1);
					glColor3f(1.0, 1.0, 1.0);
					glTranslatef(0.0, radius + TEXT_Y_OFFSET, 0.0); //Text floats above sphere
					glRotatef((GLfloat)-OpenGlScene::getRotation(), 0, 1, 0); //Ensure text is readable by user regardless of rotation
					glScalef(TEXT_SCALE, TEXT_SCALE, TEXT_SCALE); //Original scale is MASSIVE; scale the text down
					glutStrokeString(GLUT_STROKE_ROMAN,(unsigned char*)text.c_str());

					glEnable(GL_LIGHTING);
				}
	glPopMatrix(); //Restore pre-Sphere modelview matrix

}
