#ifndef COORDINATOR_HPP_INCLUDED
#define COORDINATOR_HPP_INCLUDED

#include "../Utilities/Interval.hpp"
#include "../MathHelper/MathHelper.hpp"
#include <tuple>

class DataPoint;

class Coordinator
{
	public:
		Coordinator(float w, float h);
		~Coordinator(void);

		MHTypes::Point3D getOrigin(void);
		MHTypes::Point3D getCenter(void);
		MHTypes::Point3D getPosition(DataPoint* data);
		MHTypes::Point3D getPosition(MHTypes::Point3D unitPoint);
		double getMeasuringUnits(int xyz,
								 int subdivisions,
								 int index);

		const std::tuple<double, double, double> getScale(void);
		const std::tuple<double, double, double> getSize(void);

	private:
		MHTypes::Point3D orig;
		float width, height;
		Interval latInt, lonInt, timeInt;
		std::tuple<double, double, double> scale;
		std::tuple<double, double, double> size;

		void init(void);
		void calcScale(void);
};
#endif
