#pragma once
#include <boost\date_time\gregorian\gregorian.hpp>

using boost::gregorian::date;

class IDayCounter
{
public:
	IDayCounter() = default;
	virtual ~IDayCounter() = default;
	virtual double countDayBetween(date startDate, date endDate) const = 0;
	virtual double calculateYearFraction(date startDate, date endDate) const = 0;
};

