#pragma once
#include <memory>
#include "ICreditCurve.h"
#include "IDayCounter.h"

namespace qff {
class FlatHazardRateCurve final : public ICreditCurve {
 public:
  FlatHazardRateCurve() = default;
  FlatHazardRateCurve(boost::gregorian::date curve_date, double hazard_rate,
                      const IDayCounter& day_counter);

  boost::gregorian::date GetCurveDate() const;

  double GetSurvivalProbability(
      const boost::gregorian::date& query_date) const override;
  double GetSurvivalProbability(double query_time) const override;

 private:
  boost::gregorian::date curve_date_;
  double hazard_rate_;
  std::unique_ptr<IDayCounter> day_counter_;
};
}  // namespace qff