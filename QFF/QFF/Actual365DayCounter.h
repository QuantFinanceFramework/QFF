#pragma once
#include "IDayCounter.h"

class Actual365DayCounter :
	public IDayCounter
{
public:
	Actual365DayCounter() = default;
	~Actual365DayCounter() = default;
	double countDayBetween(date startDate, date endDate) const override;
	double calculateYearFraction(date startDate, date endDate) const override;
};

