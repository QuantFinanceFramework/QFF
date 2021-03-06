#pragma once
#include <algorithm>

#include "../Aad/aad_all.h"
#include "IInterpolator.h"
#include "InterestRateCurve.h"

namespace qff_a {
template <typename T>
class DiscountFactorCurve final : public InterestRateCurve<T> {
 public:
  DiscountFactorCurve(boost::gregorian::date curve_date, std::string curve_name,
                      const IDayCounter& day_counter,
                      const IInterpolator<T>& interpolator,
                      std::vector<boost::gregorian::date> pillar_dates,
                      const std::vector<T>& discount_factors);

  T GetDiscountFactorImpl(double time) const override;

  void PutOnTape() const override;

  IrDeltas GetAdjoints() const override;

 private:
  std::unique_ptr<IInterpolator<T>> interpolator_;
  std::vector<boost::gregorian::date> pillar_dates_;
  std::map<double, T> discount_factors_map_;
};

template <typename T>
DiscountFactorCurve<T>::DiscountFactorCurve(
    boost::gregorian::date curve_date, std::string curve_name,
    const IDayCounter& day_counter, const IInterpolator<T>& interpolator,
    std::vector<boost::gregorian::date> pillar_dates,
    const std::vector<T>& discount_factors)
    : InterestRateCurve<T>(curve_date, curve_name, day_counter),
      interpolator_(interpolator.Clone()),
      pillar_dates_(std::move(pillar_dates)) {
  std::transform(
      pillar_dates_.begin(), pillar_dates_.end(), discount_factors.begin(),
      std::inserter(discount_factors_map_, discount_factors_map_.end()),
      [&](auto date, auto discount_factor) {
        return std::make_pair(
            DateToTime(*InterestRateCurve<T>::day_counter_,
                       InterestRateCurve<T>::curve_date_, date),
            discount_factor);
      });
}
template <typename T>
T DiscountFactorCurve<T>::GetDiscountFactorImpl(double time) const {
  return interpolator_->Interpol(time, discount_factors_map_);
}

template <typename T>
void DiscountFactorCurve<T>::PutOnTape() const {}

template <>
void DiscountFactorCurve<aad::a_double>::PutOnTape() const {
  for (auto& m : discount_factors_map_) {
    const_cast<aad::a_double&>(m.second).put_on_tape();
  }
}

template <typename T>
IrDeltas DiscountFactorCurve<T>::GetAdjoints() const {
  return IrDeltas{};
}

template <>
inline IrDeltas DiscountFactorCurve<aad::a_double>::GetAdjoints() const {
  std::vector<std::string> pillar;
  std::transform(pillar_dates_.begin(), pillar_dates_.end(),
                 std::back_inserter(pillar), [&](const auto& d) {
                   return GetCurveName() + "_" +
                          boost::gregorian::to_iso_extended_string(d);
                 });

  std::vector<double> deltas;
  std::transform(discount_factors_map_.begin(), discount_factors_map_.end(),
                 std::back_inserter(deltas),
                 [](const auto& m) { return m.second.adjoint(); });

  return IrDeltas{std::move(pillar), std::move(deltas)};
}
}  // namespace qff_a