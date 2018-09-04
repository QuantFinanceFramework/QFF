#include "LocalDiscountCurveApproximator.h"

LocalDiscountCurveApproximator::LocalDiscountCurveApproximator(shared_ptr<IDiscountCurveExtrapolator> leftExtrapolator,
	shared_ptr<IDiscountCurveExtrapolator> rightExtrapolator,
	shared_ptr<IDiscountCurveInterpolator> interpolator) :m_leftExtrapolator{ leftExtrapolator },
	m_rightExtrapolator{ rightExtrapolator }, m_interpolator{ interpolator } {}

double LocalDiscountCurveApproximator::approximate(date queryDate, vector<date> dates, vector<double> discountFactors) const
{
	if (queryDate < dates[0])
		return(m_leftExtrapolator->extrapol(queryDate, dates, discountFactors));
	else if (queryDate > dates.back())
		return(m_rightExtrapolator->extrapol(queryDate, dates, discountFactors));
	else
		return(m_interpolator->interpol(queryDate, dates, discountFactors));
}
