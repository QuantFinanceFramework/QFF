#pragma once
#include <vector>

using std::vector;

class IDiscountCurveApproximator
{
public:
	IDiscountCurveApproximator() = default;
	virtual ~IDiscountCurveApproximator() = default;

	virtual double approximate(const double & queryTime, const vector<double> & times, const vector<double> & discountFactors) const = 0;
};

