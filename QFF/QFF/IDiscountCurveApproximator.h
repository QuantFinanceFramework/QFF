#pragma once
#include <boost/date_time/gregorian/gregorian.hpp>
#include <vector>

using boost::gregorian::date;
using std::vector;

class IDiscountCurveApproximator
{
public:
	IDiscountCurveApproximator() = default;
	virtual ~IDiscountCurveApproximator() = default;

	virtual double approximate(date queryDate, vector<date> dates, vector<double> discountFactors) const = 0;
};

