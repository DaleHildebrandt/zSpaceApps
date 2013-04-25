#ifndef INTERVAL_HPP_INCLUDED
#define INTERVAL_HPP_INCLUDED

class Interval
{
	public:
		double min;
		double max;

		Interval(void);
		Interval(double min,
				 double max);
		~Interval(void);

		double size(void);
		void update(double value);
};
#endif