#include "LocalDiscountCurveApproximator.h"

LocalDiscountCurveApproximator::LocalDiscountCurveApproximator(
	shared_ptr<IDiscountCurveExtrapolator> leftExtrapolator,
	shared_ptr<IDiscountCurveExtrapolator> rightExtrapolator,
	shared_ptr<IDiscountCurveInterpolator> interpolator) :
	m_leftExtrapolator{ leftExtrapolator },
	m_rightExtrapolator{ rightExtrapolator }, 
	m_interpolator{ interpolator } {}

double LocalDiscountCurveApproximator::approximate(const double & queryTime, const vector<double> & times, const vector<double> & discountFactors) const
{
	if (queryTime < times[0])
		return(m_leftExtrapolator->extrapol(queryTime, times, discountFactors));
	else if (queryTime > times.back())
		return(m_rightExtrapolator->extrapol(queryTime, times, discountFactors));
	else
		return(m_interpolator->interpol(queryTime, times, discountFactors));
}
