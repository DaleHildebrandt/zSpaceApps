//DataPath.cpp
//Houses a series of data points contained within a single path.
#include "DataPath.h"

//constructor
DataPath::DataPath()
{

}

//destructor
DataPath::~DataPath()
{

}

//Adds the next point in the path
//The order in which points are added will determine
//how the polyline for the path is drawn
void DataPath::addPoint(DataPoint *data)
{

    if (points.empty())
        id = data->getID();
	points.push_back(data);

}

//Gets the id of the path
int DataPath::getId(void)
{
	return id;
}

//Get all the points in this path
vector<DataPoint*> DataPath::getPoints(void)
{
	return points;
}
