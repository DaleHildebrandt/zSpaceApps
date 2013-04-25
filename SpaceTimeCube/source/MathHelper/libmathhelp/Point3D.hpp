/*
 * Copyright (C) 2009-2012 David C. McCallum
 * For conditions of distribution and use, see the copyright notice in MathHelper.hpp
*/

/* DESCRIPTION
    A 3D point.
*/

#ifndef MH_POINT3D
#define MH_POINT3D

#include <vector>
#include <math.h>
#include "MHSettings.hpp"

namespace MHTypes
{
    class EulerAngle;

    class MH_INTERFACE Point3D
    {
        public:
            //constructors
            Point3D(void);
            Point3D(MHTypes::MHFloat newX,
                    MHTypes::MHFloat newY,
                    MHTypes::MHFloat newZ);
            Point3D(const Point3D &source);

            //overloaded = operator
            Point3D& operator= (const Point3D &source);

            //overloaded == operator
            bool operator== (const Point3D &point);

            //overloaded != operator
            bool operator!= (const Point3D &point);

            //Copies coordinates from source
            void copyFrom(const Point3D &source);

			//Return the midpoint between this point and pointTwo
			Point3D midpoint(const Point3D &pointTwo);

            //Returns the distance between this point and pointTwo
            MHFloat distance(const Point3D &pointTwo);

            //Returns the distance between this point and
            //the line defined by points a and b
            MHFloat distance(const Point3D &a,
                             const Point3D &b);

            //Returns the angle between this point and pointTwo in degrees.
            EulerAngle angleDeg(const Point3D &pointTwo);

            //this point's coordinates
            MHTypes::MHFloat x;
            MHTypes::MHFloat y;
            MHTypes::MHFloat z;

    };//Point3D
}//namespace MathHelperTypes

#endif
