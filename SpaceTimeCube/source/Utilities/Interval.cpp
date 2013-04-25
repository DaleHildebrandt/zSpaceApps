//Interval.cpp
//Contains an interval, capped at the ends by minimum and maximum values.
#include "Interval.hpp"

Interval::Interval(void)
{
	min = -1;
	max = -1;
}

Interval::Interval(double min,
				   double max)
{
	this->min = min;
	this->max = max;
}

Interval::~Interval(void)
{
}

double Interval::size(void)
{
	return max - min;
}

void Interval::update(double value)
{
	if ((max == -1) && (min == -1))
	{
		max = value;
		min = value;
	}

	else
	{
		if (value > max)
			max = value;

		else if (value < min)
			min = value;
	}

}