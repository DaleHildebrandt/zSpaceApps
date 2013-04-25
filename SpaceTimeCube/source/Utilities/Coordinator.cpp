//Coordinator.cpp
//Takes the longitude and latitude of a datapoint and converts
//it into an appropriate 3D point for display in the space time
//cube
#include "Coordinator.hpp"
#include "../Objects/DataPoint.hpp"
#include "../DataAccess/DataAccessInterface.hpp"
#include <sstream>
#include <Windows.h>

using namespace std;
using namespace MHTypes;

//constructor
Coordinator::Coordinator(float w, float h)
{
	orig = Point3D(0.0, 0, 0);
	latInt = DataAccessInterface::getLatInterval();
	lonInt = DataAccessInterface::getLonInterval();
	timeInt = DataAccessInterface::getTimeInterval();

	width = w;
	height = h;

	init();
}

void Coordinator::init(void)
{
	ostringstream ss;
	cout << "Coordinator::init : Latitude min=" << latInt.min << "  max=" << latInt.max << endl;
	cout << "Coordinator::init : Longitude min=" << lonInt.min << "  max=" << lonInt.max << endl;
	cout << "Coordinator::init: Time min=" << timeInt.min << "  max=" << timeInt.max << endl;
	latInt.min = 49.747456363;
    latInt.max = 49.96630595;
    lonInt.min = -97.3229968;
    lonInt.max = -96.9626933;

	if ((width == -1) || (height == -1))
	{
		cout << "Coordinator::init : Invalid aspect ratio." << endl;
		ss << "Coordinator::init : Invalid aspect ratio." << endl;
		OutputDebugString(ss.str().c_str());
		throw 1;
	}
	else if ((latInt.min == latInt.max) && (lonInt.min == lonInt.max) && (timeInt.min == timeInt.max))
	{
		cout << "Coordinator::init : All intervals are the same are the same." << endl;
		ss << "Coordinator::init : All intervals are the same are the same." << endl;
		OutputDebugString(ss.str().c_str());
		throw 1;
	}
	else
	{
		////adjust graph according to the aspect ration given by the width and the height
		//cout << "Coordinator::init : Width = " << width << "  Height = " << height << endl;
		//int avg = (width + height) / 2;
		//cout << "Coordinator::init : Avg = " << avg << endl;
		//int x = avg / 7;
		//cout << "Coordinator::init : X = " << x << endl;
		//size = tuple<double, double, double>(width/x, 4, height/x);
		//cout << "Coordinator::init : size(" << get<0>(size) << ", " << get<1>(size) << ", " << get<2>(size) << ")" << endl;

		size = tuple<double, double, double>(width, 0.3, height);

		calcScale();
	}
}

void Coordinator::calcScale(void)
{
	get<0>(scale) = ( get<0>(size) ) / lonInt.size();		//x scale
	get<1>(scale) = ( get<1>(size) ) / timeInt.size();		//y scale
	get<2>(scale) = ( get<2>(size) ) / latInt.size();		//z scale

	/*cout << "Scale: x=" << get<0>(scale) << " y=" << get<1>(scale) << " z=" << get<2>(scale) << endl;*/
}

Coordinator::~Coordinator(void)
{

}

Point3D Coordinator::getOrigin(void)
{
	return orig;
}

Point3D Coordinator::getCenter(void)
{
    Point3D result;

    result.x = orig.x + (get<0>(size) / 2);
    result.y = orig.y + (get<1>(size) / 2);
    result.z = orig.z - (get<2>(size) / 2);

	return result;
}
double Coordinator::getMeasuringUnits(int xyz,
									  int subdivisions,
									  int index)
{
	double result;

	switch(xyz)
	{
		case 0:
			result = ((lonInt.size() / subdivisions) * index) + lonInt.min;
			break;
		case 1:
			result = ((timeInt.size() / subdivisions) * index) + timeInt.min;
			break;
		case 2:
			result = ((latInt.size() / subdivisions) * index) + latInt.min;
			break;
		default:
			cout << "Coordinator::getMeasuringUnits : invalid xyz value" << endl;
			throw 1;
			exit(1);
	}

	return result;
}

Point3D Coordinator::getPosition(DataPoint *data)
{
	Point3D pos;
	Point2D pix;
	double time;

	//double time = ((data->getTime() - timeInt.min) * get<1>(scale)) + orig.y;
	time = ((data->getTime() - timeInt.min) * get<1>(scale));
	time = (orig.y + get<1>(size)) - time;

	pix.x = ((data->getLongitude() - lonInt.min) / (lonInt.max - lonInt.min));
	pix.y = ((data->getLatitude() - latInt.max) / (latInt.min - latInt.max));

	pos.x = (pix.x * get<0>(size)) + orig.x;
	pos.y = time;
	pos.z = (pix.y * get<2>(size)) - get<2>(size);

	//cout << "Coordinator::getPosition : Point = " << pos.x << ", " << pos.y << ", " << pos.z << endl;

	return pos;
}

Point3D Coordinator::getPosition(Point3D unitPoint)
{
	Point3D result;

	if (unitPoint.x == 0)
		result.x = orig.x;

	else if (unitPoint.x == 1)
		result.x = orig.x + get<0>(size);

	else
		cout << "Coordinator::getPosition : Invalid unitPoint (x)" << endl;

	if (unitPoint.y == 0)
		result.y = orig.y;

	else if (unitPoint.y == 1)
		result.y = orig.y + get<1>(size);

	else
		cout << "Coordinator::getPosition : Invalid unitPoint (y)" << endl;

	if (unitPoint.z == 0)
		result.z = orig.z;

	else if (unitPoint.z == 1)
		result.z = orig.z - get<2>(size);

	else
		cout << "Coordinator::getPosition : Invalid unitPoint (z)" << endl;


	//cout << "Coordinator::getPosition : Unit Point = " << result.x << ", " << result.y << ", " << result.z << endl;
	return result;
}




const tuple<double, double, double> Coordinator::getScale(void)
{
	return scale;
}

const tuple<double, double, double> Coordinator::getSize(void)
{
	return size;
}
