#include "DiscountCurve.h"

DiscountCurve::DiscountCurve(vector<date> dates, vector<double> discountFactors, 
	shared_ptr<IDiscountCurveApproximator> approximator, shared_ptr<IDayCounter> dayCounter):
	m_dates{ dates }, m_discountFactors{ discountFactors }, m_approximator{ approximator }, m_dayCounter{dayCounter}{}

double DiscountCurve::getDiscountFactor(date date) const
{
	return 0.0;
}

double DiscountCurve::getDiscountFactor(double t) const
{
	return 0.0;
}

double DiscountCurve::getForwardRate(date startDate, date endDate) const
{
	return 0.0;
}

double DiscountCurve::getZeroRate(date date) const
{
	return 0.0;
}
