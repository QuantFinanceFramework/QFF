#pragma once
#include "IDayCounter.h"
#include <boost\date_time\gregorian\gregorian.hpp>

using boost::gregorian::date;

class Actual365DayCounter :
	public IDayCounter
{
public:
	Actual365DayCounter(date startDate, date endDate);
	~Actual365DayCounter() = default;
	double countDayBetween() const override;
	double calculateYearFraction() const override;

private:
	date m_startDate;
	date m_endDate;
};

