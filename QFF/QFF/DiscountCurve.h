#pragma once
#include <vector>
#include <boost\date_time\gregorian\gregorian.hpp>
#include "IDayCounter.h"
#include "IInterpolator.h"

using std::vector;
using boost::gregorian::date;

class DiscountCurve
{
public:
	DiscountCurve() = delete;
	virtual ~DiscountCurve() = default;
	double getDiscountFactor(date date) const;
	double getForwardRate(date startDate, date endDate) const;
	double getZeroRate(date date) const;

private:
	vector<date> m_dates;
	vector<double> m_values;
	IInterpolator* m_interpolator;
	IDayCounter* m_dayCounter;
};

