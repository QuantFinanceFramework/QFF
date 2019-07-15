#pragma once
#include "IInterestRateCurve.h"
#include "IDayCounter.h"
#include "IInterpolator.h"
#include <vector>
#include <memory>

using std::vector;
using std::unique_ptr;
using std::map;

class DiscountFactorCurve :
	public IInterestRateCurve
{
public:
	DiscountFactorCurve() = default;
	DiscountFactorCurve(date curveDate, 
		const vector<date>& dates, 
		const vector<double>& discountFactors,
		const IInterpolator& interpolator,
		const IDayCounter& daycounter);
	~DiscountFactorCurve() = default;

	date getCurveDate() const;

	double getDiscountFactor(const date& queryDate) const override;
	double getDiscountFactor(double queryTime) const override;

	double getForwardRate(const date& startDate, const date& endDate) const override;
	double getForwardRate(double starttime, double endtime) const override;

	double getZeroRate(const date& queryDate) const override;
	double getZeroRate(double queryTime) const override;

private:
	double dateToTime(const date& date) const;

	date curveDate_;
	vector<date> dates_;
	map<double, double> DiscountFactorsMap_;
	unique_ptr<IInterpolator> interpolator_;
	unique_ptr<IDayCounter> dayCounter_;
};

