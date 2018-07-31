#include "Actual365DayCounter.h"

Actual365DayCounter::Actual365DayCounter(date startDate, date endDate) :m_startDate(startDate), m_endDate(endDate) {}

double Actual365DayCounter::countDayBetween() const
{
	boost::gregorian::date_duration difference = m_startDate - m_endDate;

	return difference.days();
}

double Actual365DayCounter::calculateYearFraction() const
{
	boost::gregorian::date_duration difference = m_startDate - m_endDate;

	return (difference.days()) / 365;
}
