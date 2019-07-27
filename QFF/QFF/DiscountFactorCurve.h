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

  DiscountFactorCurve(date curve_date, vector<date> dates,
                      const vector<double>& discount_factors,
                      const IInterpolator& interpolator,
                      const IDayCounter& day_counter);

  ~DiscountFactorCurve() = default;

  date GetCurveDate() const;

  double GetDiscountFactor(const date& query_date) const override;
  double GetDiscountFactor(double query_time) const override;

  double GetForwardRate(const date& start_date,
                        const date& end_date) const override;
  double GetForwardRate(double start_time, double end_time) const override;

  double GetZeroRate(const date& query_date) const override;
  double GetZeroRate(double query_time) const override;

 private:
  double DateToTime(const date& date) const;

  date curve_date_;
  vector<date> dates_;
  map<double, double> discount_factors_map_;
  unique_ptr<IInterpolator> interpolator_;
  unique_ptr<IDayCounter> day_counter_;
};
}  // namespace qff