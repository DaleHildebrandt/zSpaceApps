#ifndef DATAACCESSINTERFACE_HPP_INCLUDED
#define DATAACCESSINTERFACE_HPP_INCLUDED

#include <vector>

class DataPoint;
class Interval;

class DataAccessInterface
{
	public:
		static Interval getLatInterval(void);
		static Interval getLonInterval(void);
		static Interval getTimeInterval(void);

		virtual void loadData(void) = 0;
		virtual std::vector<DataPoint*> getData(void) = 0;
		virtual std::vector<int> getIDs(void) = 0;

	protected:
		static Interval latInterval;
		static Interval lonInterval;
		static Interval timeInterval;
};
#endif