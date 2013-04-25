//DataPoint.cpp
//Represents all the data associated with a particular point, as read from
//the CSV file.
#include "DataPoint.hpp"
#include <sstream>

//constructor
DataPoint::DataPoint(int id,
					 double lat,
					 double lng,
					 double time,
					 string date,
					 string detail)
{
	this->id = id;
	this->lat = lat;
	this->lng = lng;
	this->time = time;
	this->date = date;
	this->detail = detail;
}

//destructor
DataPoint::~DataPoint(void)
{
}



//Accessors
//string DataPoint::getDetail(void)
//{
//	return detail;
//}

int DataPoint::getID(void)
{
	return id;
}

double DataPoint::getLatitude(void)
{
	return lat;
}

double DataPoint::getLongitude(void)
{
	return lng;
}

double DataPoint::getTime(void)
{
	return time;
}

string DataPoint::getDate(void)
{
	return date;
}
//Get detailed annotation information for this point
string DataPoint::getDetailedText(void)
{
	ostringstream ss;
	ss << date << endl << detail << endl;
	return ss.str();
}
