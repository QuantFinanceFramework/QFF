#pragma once
#include <map>
#include <memory>
#include <vector>
#include "ICreditCurve.h"
#include "IDayCounter.h"
#include "IInterpolator.h"

namespace qff {
using std::map;
using std::vector;

class SurvivalCurve : public ICreditCurve {
 public:
  SurvivalCurve() = default;
  SurvivalCurve(date curve_date, vector<date> dates,
                const vector<double>& survival_probabilities,
                const IInterpolator& interpolator,
                const IDayCounter& day_counter);

  SurvivalCurve(date&& curve_date, vector<date>&& dates,
                map<double, double>&& survival_probabilities_map,
                unique_ptr<IInterpolator> interpolator,
                unique_ptr<IDayCounter> day_counter);

  ~SurvivalCurve() = default;

  date GetCurveDate() const;

  double GetSurvivalProbability(const date& query_date) const override;
  double GetSurvivalProbability(double query_time) const override;

 private:
  date curve_date_;
  vector<date> dates_;
  map<double, double> survival_probabilities_map_;
  unique_ptr<IInterpolator> interpolator_;
  unique_ptr<IDayCounter> day_counter_;
};
}  // namespace qff