//VisPolyLine.cpp
//Draws a series of connected line segments from a given set of sequential points.
#include "VisPolyLine.h"
#include <GL\openglut.h>
#define PI 3.14

//constructor
VisPolyLine::VisPolyLine(vector<AnnotatedPoint> points, double radius)
{
	for(int i = 0; i < points.size(); i++)
	{
		this->points.push_back(points[i].getPoint());
	}
	this->radius = radius;
}

//destructor
VisPolyLine::~VisPolyLine(void)
{
}

//Draws the VisPolyLine (a series of connected cylinders between points)
void VisPolyLine::render()
{
	for(int i = 0; i < points.size()-1; i++)
	{
		glPushMatrix();
		Point3D a = points[i];
		Point3D b = points[i+1];

		// This is the default direction for the cylinders to face in OpenGL
		MHVector z = MHVector(0,0,1);         
		// Get diff between two points you want cylinder along
		MHVector p = MHVector(a.x-b.x,a.y-b.y,a.z-b.z);                          
		// Get CROSS product (the axis of rotation)
		MHVector t = z.crossProduct(p);

		// Get angle; LENGTH is magnitude of the vector
		double angle = 180 / PI * acos (z.dotProduct(p) / p.length());

		//Orient & position the cylinder to connect points a & b
		glTranslated(b.x,b.y,b.z);
		glRotated(angle,t.x,t.y,t.z);

		//Drawing cylinder
		GLUquadricObj *quadric=gluNewQuadric();
		gluQuadricNormals(quadric, GLU_SMOOTH);
		gluQuadricOrientation(quadric,GLU_OUTSIDE);
		gluCylinder(quadric, radius, radius, p.length(), 36, 18);

		gluDeleteQuadric(quadric);
		glPopMatrix();
	}

}
