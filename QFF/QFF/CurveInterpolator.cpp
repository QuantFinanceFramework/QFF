#include "CurveInterpolator.h"

namespace qff {
	double CurveInterpolator::interpol(const double& queryTime, const map<double, double>& data) const
	{
		if (queryTime < data.begin()->first)
			return(leftExtrapolFunc_(queryTime, data));
		else if (queryTime > data.end()->first)
			return(rightExtrapolFunc_(queryTime, data));
		else
			return(interpolFunc_(queryTime, data));
	}
}