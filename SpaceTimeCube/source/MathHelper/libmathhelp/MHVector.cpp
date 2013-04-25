/*
 * Copyright (C) 2009-2012 David C. McCallum
 * For conditions of distribution and use, see the copyright notice in MathHelper.hpp
*/

#include "MHVector.hpp"
#include "Point3D.hpp"
#include "Quaternion.hpp"
#include "Matrix3x3.hpp"
#include "EulerAngle.hpp"
#include "../MathHelper.hpp"
#include <math.h>

using namespace MHTypes;

MHVector::MHVector(void)
{
    x = 0;
    y = 0;
    z = 0;
}//constructor

MHVector::MHVector(MHFloat newX,
                   MHFloat newY,
                   MHFloat newZ)
{
    x = newX;
    y = newY;
    z = newZ;
}//constructor

MHVector::MHVector(const MHVector &source)
{
    x = source.x;
    y = source.y;
    z = source.z;
}//copy constructor

MHVector::MHVector(const Point3D &a,
				   const Point3D &b)
{
	x = b.x - a.x;
	y = b.y - a.y;
	z = b.z - a.z;
}//constructor from 2 points

MHVector& MHVector::operator= (const MHVector &source)
{
    if (this != &source)
        copyFrom(source);

    return *this;
}//=

bool MHVector::operator== (const MHVector &vec)
{
    bool result = false;

    if ( (this->x == vec.x) &&
         (this->y == vec.y) &&
         (this->z == vec.z) )
    {
        result = true;
    }

    return result;
}//==

bool MHVector::operator!= (const MHVector &vec)
{
    return !(*this == vec);
}//\!=

void MHVector::copyFrom(const MHVector &source)
{
    x = source.x;
    y = source.y;
    z = source.z;
}//copyFrom

void MHVector::fromQuaternion(const Quaternion &source)
{
    Point3D thePoint(x, y, z);//point equivalent of this vector
    Matrix3x3 rotationMatrix;//matrix corresponding to source

    rotationMatrix = source.getRotationMatrix();
    thePoint = rotationMatrix.rotatePoint(thePoint);

    x = thePoint.x;
    y = thePoint.y;
    z = thePoint.z;
}//if fromQuaternion

MHVector MHVector::normalize(void)
{
    MHVector result(*this);//the normalized vector to return
    MHFloat divisor = 0;//divide each value by this amount

    divisor = sqrt((x * x) + (y * y) + (z * z));

    if (divisor != 0)
    {
        result.x /= divisor;
        result.y /= divisor;
        result.z /= divisor;
    }//if divisor

    return result;
}//normalize

MHFloat MHVector::dotProduct(const MHVector &vectorTwo)
{
    MHVector tmp;
    MHFloat result;

    tmp.x = this->x * vectorTwo.x;
    tmp.y = this->y * vectorTwo.y;
    tmp.z = this->z * vectorTwo.z;

    result = tmp.x + tmp.y + tmp.z;

    return result;
}//dotProduct

MHVector MHVector::crossProduct(const MHVector &vectorTwo)
{
    MHVector result;//the cross product to return

    result.x = (y * vectorTwo.z) - (z * vectorTwo.y);
    result.y = (z * vectorTwo.x) - (x * vectorTwo.z);
    result.z = (x * vectorTwo.y) - (y * vectorTwo.x);

    return result;
}//crossProduct

MHFloat MHVector::length(void)
{
    Point3D origin;//0, 0, 0
    Point3D endPoint;//this vector's endpoint

    endPoint.x = x;
    endPoint.y = y;
    endPoint.z = z;

    return origin.distance(endPoint);
}//length
