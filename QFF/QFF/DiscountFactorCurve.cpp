#include "DiscountFactorCurve.h"
#include <cmath>

namespace qff {
	DiscountFactorCurve::DiscountFactorCurve(date curveDate, const vector<date>& dates,
		const vector<double>& discountFactors, const IInterpolator& interpolator,
		const IDayCounter& daycounter) {}

	DiscountFactorCurve::DiscountFactorCurve(date curveDate, const vector<date>& dates,
		const vector<double>& discountFactors, unique_ptr<IInterpolator> interpolator,
		unique_ptr<IDayCounter> daycounter) {}

	date DiscountFactorCurve::getCurveDate() const
	{
		return curveDate_;
	}

	double DiscountFactorCurve::getDiscountFactor(const date& queryDate) const
	{
		return getDiscountFactor(dateToTime(queryDate));
	}

	double DiscountFactorCurve::getDiscountFactor(double queryTime) const
	{
		return interpolator_->interpol(queryTime, discountFactorsMap_);
	}

	double DiscountFactorCurve::getForwardRate(const date& startDate, const date& endDate) const
	{
		return getForwardRate(dateToTime(startDate), dateToTime(endDate));
	}

	double DiscountFactorCurve::getForwardRate(double startTime, double endTime) const
	{
		return -log(getDiscountFactor(endTime) / getDiscountFactor(startTime)) / (endTime - startTime);
	}

	double DiscountFactorCurve::getZeroRate(const date& queryDate) const
	{
		return getZeroRate(dateToTime(queryDate));
	}

	double DiscountFactorCurve::getZeroRate(double queryTime) const
	{
		return -log(getDiscountFactor(queryTime)) / queryTime;
	}

	double DiscountFactorCurve::dateToTime(const date& date) const
	{
		return dayCounter_->calculateYearFraction(curveDate_, date);
	}
}