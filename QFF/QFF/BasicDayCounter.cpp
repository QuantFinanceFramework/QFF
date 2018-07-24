#include "BasicDayCounter.h"

BasicDayCounter::BasicDayCounter(date startDate, date endDate) :m_startDate(startDate), m_endDate(endDate) {}

double BasicDayCounter::countDayBetween() const
{
	double difference = (m_startDate - m_endDate).days();

	return difference;
}

double BasicDayCounter::calculateYearFraction() const
{
	double difference = (m_startDate - m_endDate).days();

	return difference / 365;
}
