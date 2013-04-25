//DataAccessCSV.cpp
//Reads in data from a CSV file, provides higher-level accessors to that data.

#include "DataAccessCSV.hpp"
#include "../Objects/DataPoint.hpp"
#include "../Utilities/Parser.hpp"
#include "../Utilities/Interval.hpp"

#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include <Windows.h>

//Constructor
DataAccessCSV::DataAccessCSV(const string &filename, float width, float height)
{
	this->filename = filename;
	loadData();
	organizeData();
	this->coordinator = new Coordinator(width, height);
}

//Destructor
DataAccessCSV::~DataAccessCSV(void)
{
	data.erase(data.begin(), data.end());
}

//Loads data from a CSV file (file given on creation of a DataAccessCSV object)
void DataAccessCSV::loadData(void)
{
	//parse data file
	ifstream file;
	string line;
	int count = 0;

	file.open(filename.c_str());
	if (file.is_open())
	{
		while(file.good())
		{
			getline(file, line);

			if (count > 0)
				processLine(line);

			count++;
		}
		file.close();
	}
	else
	{
        cout << "DataAccessCSV::loadData() - file couldn't be opened" << endl;
        throw 1;
	}
}

//Organize data into paths
void DataAccessCSV::organizeData(void)
{
	cout << "AccessPoints::init - initializing..." << endl;
    int id;

    std::map<int, DataPath*>::iterator it;
    DataPath *path;

    cout << "AccessPoints::init - getting data" << endl;

	for (int i = 0; i < data.size(); i++)
	{
		//find the path with the data's id
		id = data[i]->getID();

		it = paths.find(id);
		if (it == paths.end())
        {
			ids.push_back(id);
            path = new DataPath();
            paths.insert(pair<int, DataPath*>(id, path));
        }//if we need to create a new path
        cout << "AccessPoints::init - calling addPoint" << endl;
        //add the datapoint to the path
        path->addPoint(data[i]);
	}

}

//Accessors
//Return all of the datapoints from the CSV file
vector<DataPoint*> DataAccessCSV::getData(void)
{
	return data;
}

//Returns all of the unique path IDs in the CSV file
vector<int> DataAccessCSV::getIDs(void)
{
	return ids;
}

//Returns the path associated with the given user ID
DataPath* DataAccessCSV::getPath(int id)
{
	return paths[id];
}

//Returns the path associated with the given user ID.
//(display path contains data relevant to drawing points to the sceen;
//normal getPath is purely for data access)
vector<AnnotatedPoint> DataAccessCSV::getDisplayPath(int id)
{
	int w, h, t;
	vector<DataPoint*> dataPath = paths[id]->getPoints();
	vector<AnnotatedPoint> displayPath;

	for(int i = 0; i < dataPath.size(); i++)
	{
		AnnotatedPoint currPoint = AnnotatedPoint(coordinator->getPosition(dataPath[i]), dataPath[i]->getDetailedText());
		displayPath.push_back(currPoint);
	}
	return displayPath;
}

//Process a line from the CSV file
void DataAccessCSV::processLine(const string &line)
{
	vector<string> row;
	Parser parser;
	string tmp, detail;
	int id, date;
	double lon, lat;

	row = parser.tokenize(line, ",");

	if (row.size() >= 4)
	{
		//get track number
		//tmp = row[0].substr(row[0].size()-1, row[0].size());
		tmp = row[0];

		if (!(parser.stringIsInt(tmp)))
		{
			cout << "DataAccessCSV::processLine : id = " << tmp << endl;
			exit(1);
		}
		id = parser.string2Int(tmp);

		//get Detailed Info (dataset1 does not have this; only useful for dataset2)
		detail = row[1];

		//get latitude
		tmp = row[row.size() - 3];
		if (!(parser.stringIsDouble(tmp)))
		{
			cout << "DataAccessCSV::processLine : lat = " << tmp << endl;
			exit(1);
		}
		lat = parser.string2Double(tmp);
		latInterval.update(lat);

		//get longitude
		tmp = row[row.size() - 2];
		if (!(parser.stringIsDouble(tmp)))
		{
			cout << "DataAccessCSV::processLine : lon = " << tmp << endl;
			exit(1);
		}
		lon = parser.string2Double(tmp);
		lonInterval.update(lon);

		//get Date
		tmp = row[row.size() - 1];
		if (!(parser.stringIsDate(tmp)))
		{
			cout << "DataAccessCSV::processLine : time = " << tmp << endl;
			exit(1);
		}
		date = parser.string2Date(tmp);
		timeInterval.update(date);

		//Thin out the data
		if ( ( data.size() == 0 ) ||
             ( data.back()->getID() != id) ||
             ( data.back()->getTime() < date - 1) )
        {
            data.push_back(new DataPoint(id, lat, lon, date, tmp, detail));
        }
	}
}
