#pragma once
#include <boost\date_time\gregorian\gregorian.hpp>

using boost::gregorian::date;

class IInterestRateCurve
{
public:
	IInterestRateCurve() = default;
	virtual ~IInterestRateCurve() = default;

	virtual double getDiscountFactor(const date& queryDate) const = 0;
	virtual double getDiscountFactor(double queryTime) const = 0;

	virtual double getForwardRate(const date& startDate, const date& endDate) const = 0;
	virtual double getForwardRate(double starttime, double endtime) const = 0;

	virtual double getZeroRate(const date& queryDate) const = 0;
	virtual double getZeroRate(double queryTime) const = 0;
};

