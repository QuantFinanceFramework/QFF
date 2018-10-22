#pragma once
#include <vector>

using std::vector;

class IDiscountCurveExtrapolator
{
public:
	IDiscountCurveExtrapolator() = default;
	virtual ~IDiscountCurveExtrapolator() = default;

	virtual double extrapol(const double & queryTime, const vector<double> & times, const vector<double> & discountFactors) const = 0;
};
