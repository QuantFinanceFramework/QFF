#include "Actual365DayCounter.h"

double Actual365DayCounter::countDayBetween(date startDate, date endDate) const
{
	boost::gregorian::date_duration difference = startDate - endDate;

	return difference.days();
}

double Actual365DayCounter::calculateYearFraction(date startDate, date endDate) const
{
	return countDayBetween(startDate, endDate) / 365;
}
