#pragma once
#include <memory>
#include "IDayCounter.h"
#include "IInterestRateCurve.h"

namespace qff {

class FlatZeroCurve final : public IInterestRateCurve {
 public:
  FlatZeroCurve() = default;
  FlatZeroCurve(boost::gregorian::date curve_date, double zero_rate,
                const IDayCounter& day_counter);

  boost::gregorian::date GetCurveDate() const;

  double GetDiscountFactor(
      const boost::gregorian::date& query_date) const override;
  double GetDiscountFactor(double query_time) const override;
  double GetForwardRate(const boost::gregorian::date& start_date,
                        const boost::gregorian::date& end_date) const override;
  double GetForwardRate(double start_time, double end_time) const override;
  double GetZeroRate(const boost::gregorian::date& query_date) const override;
  double GetZeroRate(double query_time) const override;

 private:
  boost::gregorian::date curve_date_;
  double zero_rate_;
  std::unique_ptr<IDayCounter> day_counter_;
};
}  // namespace qff