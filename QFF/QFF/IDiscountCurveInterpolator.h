#pragma once
#include <boost/date_time/gregorian/gregorian.hpp>
#include <vector>

using boost::gregorian::date;
using std::vector;

class IDiscountCurveInterpolator
{
public:
	IDiscountCurveInterpolator() = default;
	virtual ~IDiscountCurveInterpolator() = default;

	virtual double interpol(date queryDate, vector<date> dates, vector<double> discountFactors) const = 0;
};
