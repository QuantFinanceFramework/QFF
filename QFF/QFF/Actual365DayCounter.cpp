#include "Actual365DayCounter.h"

Actual365DayCounter::Actual365DayCounter(date startDate, date endDate) :m_startDate(startDate), m_endDate(endDate) {}

double Actual365DayCounter::countDayBetween() const
{
	double difference = (m_startDate - m_endDate).days();

	return difference;
}

double Actual365DayCounter::calculateYearFraction() const
{
	double difference = (m_startDate - m_endDate).days();

	return difference / 365;
}
