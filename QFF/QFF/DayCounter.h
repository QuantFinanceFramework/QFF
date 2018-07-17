#pragma once
#include "IDayCounter.h"
#include <boost\date_time\gregorian\gregorian.hpp>

using namespace boost::gregorian;

class DayCounter :
	public IDayCounter
{
public:
	DayCounter(date startDate, date endDate);
	~DayCounter() = default;
	double calculate() const override;
	double calculateYearFraction() const;

private:
	date m_startDate;
	date m_endDate;
};

