#pragma once
#include "IDayCounter.h"
#include <boost\date_time\gregorian\gregorian.hpp>

using boost::gregorian::date;

class BasicDayCounter :
	public IDayCounter
{
public:
	BasicDayCounter(date startDate, date endDate);
	~BasicDayCounter() = default;
	double countDayBetween() const override;
	double calculateYearFraction() const override;

private:
	date m_startDate;
	date m_endDate;
};

