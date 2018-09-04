#pragma once
#include <boost/date_time/gregorian/gregorian.hpp>
#include <vector>

using boost::gregorian::date;
using std::vector;

class IDiscountCurveExtrapolator
{
public:
	IDiscountCurveExtrapolator() = default;
	virtual ~IDiscountCurveExtrapolator() = default;

	virtual double extrapol(date queryDate, vector<date> dates, vector<double> discountFactors) const = 0;
};
