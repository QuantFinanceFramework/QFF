#pragma once
#include <memory>
#include "IDayCounter.h"
#include "IInterestRateCurve.h"

namespace qff {
using std::unique_ptr;

class FlatZeroCurve : public IInterestRateCurve {
 public:
  FlatZeroCurve() = default;
  FlatZeroCurve(date curve_date, double zero_rate, const IDayCounter& day_counter);
  ~FlatZeroCurve() = default;

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
  double zero_rate_;
  unique_ptr<IDayCounter> day_counter_;
};
}  // namespace qff