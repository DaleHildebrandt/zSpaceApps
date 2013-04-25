/*
 * Copyright (C) 2009-2012 David C. McCallum
 * For conditions of distribution and use, see the copyright notice in MathHelper.hpp
*/

#include "EulerAngle.hpp"
#include "Quaternion.hpp"
#include <math.h>

using namespace MHTypes;
using namespace std;

EulerAngle::EulerAngle(void)
{
    pitch = 0;
    yaw = 0;
    roll = 0;
}//constructor

EulerAngle::EulerAngle(MHFloat newPitch,
                       MHFloat newYaw,
                       MHFloat newRoll)
{
    pitch = newPitch;
    yaw = newYaw;
    roll = newRoll;
}//constructor

EulerAngle::EulerAngle(const EulerAngle &source)
{
    pitch = source.pitch;
    yaw = source.yaw;
    roll = source.roll;
}//copy constructor

EulerAngle::~EulerAngle(void)
{
}//destructor

EulerAngle& EulerAngle::operator= (const EulerAngle &source)
{
    if (this != &source)
        copyFrom(source);

    return *this;
}//=

bool EulerAngle::operator== (const EulerAngle &angle)
{
    bool result = false;

    if ( (this->pitch == angle.pitch) &&
         (this->yaw == angle.yaw) &&
         (this->roll == angle.roll))
    {
        result = true;
    }

    return result;
}//==

bool EulerAngle::operator!= (const EulerAngle &angle)
{
    return !(*this == angle);
}//\!=

void EulerAngle::copyFrom(const EulerAngle &source)
{
    pitch = source.pitch;
    yaw = source.yaw;
    roll = source.roll;
}//copyFrom
