#include "DayCounter.h"

DayCounter::DayCounter(date startDate, date endDate) :m_startDate(startDate), m_endDate(endDate) {}

double DayCounter::calculate() const
{
	double difference = (m_startDate - m_endDate).days();

	return difference;
}

double DayCounter::calculateYearFraction() const
{
	double difference = (m_startDate - m_endDate).days();

	return difference / 365;
}