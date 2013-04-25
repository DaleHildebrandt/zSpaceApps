#ifndef DATAACCESSCSV_HPP_INCLUDED
#define DATAACCESSCSV_HPP_INCLUDED

#include "DataAccessInterface.hpp"
#include "../Objects/DataPath.h"
#include <string>
#include <map>
#include "../Utilities/Coordinator.hpp"
#include "../MathHelper/MathHelper.hpp"
#include "../Objects/AnnotatedPoint.h"
using namespace std;
using namespace MHTypes;

class DataAccessCSV : public DataAccessInterface
{
	public:
		DataAccessCSV(const std::string &filename, float width, float height);
		virtual ~DataAccessCSV(void);
		virtual void loadData(void);
		virtual std::vector<DataPoint*> getData(void);
		virtual std::vector<int> getIDs(void);
		DataPath* DataAccessCSV::getPath(int id);
		vector<AnnotatedPoint> getDisplayPath(int id);
		void organizeData(void);
	private:
		std::vector<DataPoint*> data;
		std::string filename;
		std::map<int, DataPath*> paths;
		vector<int> ids;
		Coordinator* coordinator;

		void processLine(const std::string &line);



};
#endif
