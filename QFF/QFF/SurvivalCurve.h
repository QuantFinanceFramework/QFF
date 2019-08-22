#pragma once
#include <map>
#include <memory>
#include <vector>
#include "ICreditCurve.h"
#include "IDayCounter.h"
#include "IInterpolator.h"

namespace qff {

class SurvivalCurve : public ICreditCurve {
 public:
  SurvivalCurve() = default;
  SurvivalCurve(boost::gregorian::date curve_date,
                std::vector<boost::gregorian::date> dates,
                const std::vector<double>& survival_probabilities,
                const IInterpolator& interpolator,
                const IDayCounter& day_counter);

  SurvivalCurve(boost::gregorian::date&& curve_date,
                std::vector<boost::gregorian::date>&& dates,
                std::map<double, double>&& survival_probabilities_map,
                std::unique_ptr<IInterpolator> interpolator,
                std::unique_ptr<IDayCounter> day_counter);

  ~SurvivalCurve() = default;

  boost::gregorian::date GetCurveDate() const;

  double GetSurvivalProbability(
      const boost::gregorian::date& query_date) const override;
  double GetSurvivalProbability(double query_time) const override;

 private:
  boost::gregorian::date curve_date_;
  std::vector<boost::gregorian::date> dates_;
  std::map<double, double> survival_probabilities_map_;
  std::unique_ptr<IInterpolator> interpolator_;
  std::unique_ptr<IDayCounter> day_counter_;
};
}  // namespace qff