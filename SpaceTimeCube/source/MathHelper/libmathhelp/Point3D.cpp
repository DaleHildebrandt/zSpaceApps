/*
 * Copyright (C) 2009-2012 David C. McCallum
 * For conditions of distribution and use, see the copyright notice in MathHelper.hpp
*/

#include "Point3D.hpp"
#include "EulerAngle.hpp"
#include "MHVector.hpp"
#include "../MathHelper.hpp"

using namespace std;
using namespace MHTypes;

Point3D::Point3D(void)
{
    x = 0;
    y = 0;
    z = 0;
}//constructor

Point3D::Point3D(MHFloat newX,
                 MHFloat newY,
                 MHFloat newZ)
{
    x = newX;
    y = newY;
    z = newZ;
}//constructor

Point3D::Point3D(const Point3D &source)
{
    x = source.x;
    y = source.y;
    z = source.z;
}//copy constructor

Point3D& Point3D::operator= (const Point3D &source)
{
    if (this != &source)
        copyFrom(source);

    return *this;
}//=

bool Point3D::operator== (const Point3D &point)
{
    bool result = false;

    if ( (this->x == point.x) &&
         (this->y == point.y) &&
         (this->z == point.z) )
    {
        result = true;
    }

    return result;
}//==

bool Point3D::operator!= (const Point3D &point)
{
    return !(*this == point);
}//\!=

void Point3D::copyFrom(const Point3D &source)
{
    x = source.x;
    y = source.y;
    z = source.z;
}//copyFrom

Point3D Point3D::midpoint(const Point3D &pointTwo)
{
	Point3D result;

	result.x = (this->x + pointTwo.x) / 2;
	result.y = (this->y + pointTwo.y) / 2;
	result.z = (this->z + pointTwo.z) / 2;

	return result;
}//midpoint

MHFloat Point3D::distance(const Point3D &pointTwo)
{
    MHFloat horizDistance = this->x - pointTwo.x;
    MHFloat verticalDistance = this->y - pointTwo.y;
    MHFloat depthDistance = this->z - pointTwo.z;
    MHFloat result = 0;//the distance to return

    result = (horizDistance * horizDistance) + (verticalDistance * verticalDistance) + (depthDistance * depthDistance);
    result = sqrt(result);

    return result;
}//distance

MHFloat Point3D::distance(const Point3D &a,
                          const Point3D &b)
{
    MHVector v(a, b);
    MHVector w(a, *this);

    MHFloat c1 = w.dotProduct(v);
    MHFloat c2 = v.dotProduct(v);
    MHFloat q = c1 / c2;

    Point3D pq(a.x + (q * v.x),
               a.y + (q * v.y),
               a.z + (q * v.z));

    return distance(pq);
}//distance

EulerAngle Point3D::angleDeg(const Point3D &pointTwo)
{
    MHFloat length = distance(pointTwo);
    MHVector dirVec(*this, pointTwo);//the direction vector from this point to pointTwo
    EulerAngle result;//the angle to return

    //Find the vector from this point to pointTwo
	/*
    dirVec.x = pointTwo.x - x;
    dirVec.y = pointTwo.y - y;
    dirVec.z = pointTwo.z - z;
	*/
    //Set pitch to zero
    result.pitch = 0;

    //calculate yaw as arctan(-v.z / v.x) * radToDeg
    result.yaw = atan2(-dirVec.z, dirVec.x);
    result.yaw *= MathHelper::radToDeg();

    //calculate roll as arcsin(v.y / distance) * radToDeg
    result.roll = asin(dirVec.y / length);
    result.roll *= MathHelper::radToDeg();

    return result;
}//angleDeg
