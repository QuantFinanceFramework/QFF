#pragma once
#include "IDiscountCurveApproximator.h"
#include "IDiscountCurveExtrapolator.h"
#include "IDiscountCurveInterpolator.h"
#include <memory>

using std::shared_ptr;

class LocalDiscountCurveApproximator :
	public IDiscountCurveApproximator
{
public:
	LocalDiscountCurveApproximator() = delete;
	LocalDiscountCurveApproximator(
		shared_ptr<IDiscountCurveExtrapolator> leftExtrapolator, 
		shared_ptr<IDiscountCurveExtrapolator> rightExtrapolator, 
		shared_ptr<IDiscountCurveInterpolator> interpolator);

	~LocalDiscountCurveApproximator() = default;

	double approximate(const double & queryTime, const vector<double> & times, const vector<double> & discountFactors) const override;

private:
	shared_ptr<IDiscountCurveExtrapolator> m_leftExtrapolator;
	shared_ptr<IDiscountCurveExtrapolator> m_rightExtrapolator;
	shared_ptr<IDiscountCurveInterpolator> m_interpolator;
};