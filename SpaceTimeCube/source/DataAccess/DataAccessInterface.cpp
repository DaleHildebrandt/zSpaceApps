#include "DataAccessInterface.hpp"
#include "../Utilities/Interval.hpp"

Interval DataAccessInterface::latInterval;
Interval DataAccessInterface::lonInterval;
Interval DataAccessInterface::timeInterval;

Interval DataAccessInterface::getLatInterval(void)
{
	return latInterval;
}

Interval DataAccessInterface::getLonInterval(void)
{
	return lonInterval;
}

Interval DataAccessInterface::getTimeInterval(void)
{
	return timeInterval;
}