#pragma once
#include <boost\date_time\gregorian\gregorian.hpp>
#include <memory>

using boost::gregorian::date;
using std::unique_ptr;

class IDayCounter
{
public:
	IDayCounter() = default;
	virtual ~IDayCounter() = default;

	virtual unique_ptr<IDayCounter> clone() const = 0;

	virtual double countDayBetween(date startDate, date endDate) const = 0;
	virtual double calculateYearFraction(date startDate, date endDate) const = 0;
};

