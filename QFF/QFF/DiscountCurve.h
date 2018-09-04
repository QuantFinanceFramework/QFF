#pragma once
#include <vector>
#include <boost\date_time\gregorian\gregorian.hpp>
#include "IDayCounter.h"
#include "IDiscountCurveApproximator.h"
#include <memory>

using std::vector;
using boost::gregorian::date;
using std::shared_ptr;

class DiscountCurve
{
public:
	DiscountCurve() = delete;
	DiscountCurve(vector<date> dates, vector<double> discountFactors, shared_ptr<IDiscountCurveApproximator> approximator,
		shared_ptr<IDayCounter> dayCounter);
	virtual ~DiscountCurve() = default;
	double getDiscountFactor(date date) const;
	double getForwardRate(date startDate, date endDate) const;
	double getZeroRate(date date) const;

private:
	vector<date> m_dates;
	vector<double> m_discountFactors;
	shared_ptr<IDiscountCurveApproximator> m_approximator;
	shared_ptr<IDayCounter> m_dayCounter;
};

