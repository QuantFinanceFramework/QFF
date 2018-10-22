#include "DiscountCurveInterpolator.h"

DiscountCurveInterpolator::DiscountCurveInterpolator(function<double(const double &, const map<double, double> &)> interpolFunc) : m_interpolFunc{ interpolFunc }{}

double DiscountCurveInterpolator::interpol(const double & queryTime, const map<double, double>& data) const
{
	return m_interpolFunc(queryTime, data);
}
