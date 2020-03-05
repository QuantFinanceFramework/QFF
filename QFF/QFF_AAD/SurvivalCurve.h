#pragma once
#include <map>
#include <memory>
#include <vector>

#include "../AAD/expression.h"
#include "DateFunctions.h"
#include "ICreditCurve.h"
#include "IDayCounter.h"
#include "IInterpolator.h"

namespace qff_a {
template <typename T>
class SurvivalCurve final : public ICreditCurve<T> {
 public:
  SurvivalCurve(boost::gregorian::date curve_date,
                std::vector<boost::gregorian::date> pillar_dates,
                const std::vector<T>& survival_probabilities,
                const IInterpolator<T>& interpolator,
                const IDayCounter& day_counter);

  SurvivalCurve(boost::gregorian::date&& curve_date,
                std::vector<boost::gregorian::date>&& pillar_dates,
                std::map<double, T>&& survival_probabilities_map,
                std::unique_ptr<IInterpolator<T>> interpolator,
                std::unique_ptr<IDayCounter> day_counter);

  boost::gregorian::date GetCurveDate() const;

  T GetSurvivalProbability(
      const boost::gregorian::date& query_date) const override {
    return GetSurvivalProbabilityImpl(
        DateToTime(*day_counter_, curve_date_, query_date));
  }

  std::vector<double> GetAdjoints() const override;

 private:
  T GetSurvivalProbabilityImpl(double time) const;
  boost::gregorian::date curve_date_;
  std::vector<boost::gregorian::date> pillar_dates_;
  std::map<double, T> survival_probabilities_map_;
  std::unique_ptr<IInterpolator<T>> interpolator_;
  std::unique_ptr<IDayCounter> day_counter_;
};

template <typename T>
SurvivalCurve<T>::SurvivalCurve(
    boost::gregorian::date curve_date,
    std::vector<boost::gregorian::date> pillar_dates,
    const std::vector<T>& survival_probabilities,
    const IInterpolator<T>& interpolator, const IDayCounter& day_counter)
    : curve_date_(curve_date),
      pillar_dates_(std::move(pillar_dates)),
      interpolator_(interpolator.Clone()),
      day_counter_(day_counter.Clone()) {
  std::transform(pillar_dates_.begin(), pillar_dates_.end(),
                 survival_probabilities.begin(),
                 std::inserter(survival_probabilities_map_,
                               survival_probabilities_map_.end()),
                 [&](auto date, auto survival_probability) {
                   return std::make_pair(
                       DateToTime(*day_counter_, curve_date_, date),
                       survival_probability);
                 });
}

template <typename T>
SurvivalCurve<T>::SurvivalCurve(
    boost::gregorian::date&& curve_date,
    std::vector<boost::gregorian::date>&& pillar_dates,
    std::map<double, T>&& survival_probabilities_map,
    std::unique_ptr<IInterpolator<T>> interpolator,
    std::unique_ptr<IDayCounter> day_counter)
    : curve_date_(curve_date),
      pillar_dates_(pillar_dates),
      survival_probabilities_map_(survival_probabilities_map),
      interpolator_(std::move(interpolator)),
      day_counter_(std::move(day_counter)) {}

template <typename T>
boost::gregorian::date SurvivalCurve<T>::GetCurveDate() const {
  return curve_date_;
}

template <typename T>
std::vector<double> SurvivalCurve<T>::GetAdjoints() const {
  return std::vector<double>(size(pillar_dates_));
}

template <>
inline std::vector<double> SurvivalCurve<aad::a_double>::GetAdjoints() const {
  std::vector<double> adjoints(size(pillar_dates_));
  std::transform(survival_probabilities_map_.begin(),
                 survival_probabilities_map_.end(), adjoints.begin(),
                 [](const auto& itr) { return itr.second.adjoint(); });
  return adjoints;
}

template <typename T>
T SurvivalCurve<T>::GetSurvivalProbabilityImpl(double time) const {
  return T(interpolator_->Interpol(time, survival_probabilities_map_));
}
}  // namespace qff_a