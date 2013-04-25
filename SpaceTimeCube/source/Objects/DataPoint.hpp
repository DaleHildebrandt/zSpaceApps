#ifndef DATAPOINT_HPP_INCLUDED
#define DATAPOINT_HPP_INCLUDED

#include <string>

using namespace std;

class DataPoint
{
	public:
		DataPoint(int id,
				  double lat,
				  double lng,
				  double time, 
				  string date,
				  string detail);

		~DataPoint(void);

		int getID(void);
		double getLatitude(void);
		double getLongitude(void);
		double getTime(void);
		string getDate(void);
		string getDetail(void);
		string getDetailedText(void);

	private:
		int id;
		double lat;
		double lng;
		double time;
		string date;
		string detail;
        
};
#endif
