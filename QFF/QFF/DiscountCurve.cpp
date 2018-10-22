#include "DiscountCurve.h"
#include <functional>

DiscountCurve::DiscountCurve(
	vector<date> dates, 
	vector<double> discountFactors, 
	DiscountCurveInterpolator interpolator,
	shared_ptr<IDayCounter> dayCounter) :
	m_dates{ dates }, 
	m_interpolator{ interpolator },
	m_dayCounter{dayCounter}{
	for (size_t i = 0; i < dates.size(); ++i)
	{
		m_discountFactors.emplace(std::make_pair(dateToTime(dates[i]), discountFactors[i]));
	}
}

double DiscountCurve::getDiscountFactor(const date & date) const
{
	return getDiscountFactor(dateToTime(date));
}

double DiscountCurve::getDiscountFactor(double time) const
{
	return m_interpolator.interpol(time, m_discountFactors);
}

double DiscountCurve::getForwardRate(const date & startDate, const date & endDate) const
{
	return 0.0;
}

double DiscountCurve::getZeroRate(const date & date) const
{
	return 0.0;
}

double DiscountCurve::dateToTime(const date & date) const
{
	return m_dayCounter->calculateYearFraction(m_dates[0], date);
}
