#pragma once
#include <memory>
#include <vector>
#include "IDayCounter.h"
#include "IInterestRateCurve.h"
#include "IInterpolator.h"

namespace qff {
using std::map;
using std::unique_ptr;
using std::vector;

class DiscountFactorCurve : public IInterestRateCurve {
 public:
  DiscountFactorCurve() = default;

  DiscountFactorCurve(date curveDate, const vector<date>& dates,
                      const vector<double>& discountFactors,
                      const IInterpolator& interpolator,
                      const IDayCounter& daycounter);

  DiscountFactorCurve(date curveDate, const vector<date>& dates,
                      const vector<double>& discountFactors,
                      unique_ptr<IInterpolator> interpolator,
                      unique_ptr<IDayCounter> daycounter);

  ~DiscountFactorCurve() = default;

  date getCurveDate() const;

  double getDiscountFactor(const date& queryDate) const override;
  double getDiscountFactor(double queryTime) const override;

  double getForwardRate(const date& startDate,
                        const date& endDate) const override;
  double getForwardRate(double startTime, double endTime) const override;

  double getZeroRate(const date& queryDate) const override;
  double getZeroRate(double queryTime) const override;

 private:
  double dateToTime(const date& date) const;

  date curveDate_;
  vector<date> dates_;
  map<double, double> discountFactorsMap_;
  unique_ptr<IInterpolator> interpolator_;
  unique_ptr<IDayCounter> dayCounter_;
};
}  // namespace qff