#pragma once
#include "DataPoint.hpp"
#include <stdlib.h>
#include <vector>

using namespace std;

class DataPath
{
public:
	DataPath(void);
	~DataPath(void);
	void addPoint(DataPoint* data);
	vector<DataPoint*> getPoints(void);
	int getId(void);
private:
	std::vector<DataPoint*> points;
	int id;
};

