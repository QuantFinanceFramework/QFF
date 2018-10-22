#pragma once
#include <vector>
#include <boost\date_time\gregorian\gregorian.hpp>
#include "IDayCounter.h"
#include "DiscountCurveInterpolator.h"
#include <memory>
#include <map>

using std::vector;
using boost::gregorian::date;
using std::shared_ptr;
using std::map;

class DiscountCurve
{
public:
	DiscountCurve() = delete;
	DiscountCurve(vector<date> dates, vector<double> discountFactors, DiscountCurveInterpolator interpolator,
		shared_ptr<IDayCounter> dayCounter);
	virtual ~DiscountCurve() = default;
	double getDiscountFactor(const date & date) const;
	double getDiscountFactor(double time) const;
	double getForwardRate(const date & startDate, const date & endDate) const;
	double getZeroRate(const date & date) const;

private:
	vector<date> m_dates;
	map<double, double> m_discountFactors;
	DiscountCurveInterpolator m_interpolator;
	shared_ptr<IDayCounter> m_dayCounter;

	double dateToTime(const date & date) const;
};

