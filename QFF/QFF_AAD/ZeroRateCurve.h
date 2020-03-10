#pragma once
#include <algorithm>

#include "../AAD/aad_all.h"
#include "IInterpolator.h"
#include "InterestRateCurve.h"

namespace qff_a {
template <typename T>
class ZeroRateCurve final : public InterestRateCurve<T> {
 public:
  ZeroRateCurve(boost::gregorian::date curve_date, std::string curve_name,
                const IDayCounter& day_counter,
                const IInterpolator<T>& interpolator,
                std::vector<boost::gregorian::date> pillar_dates,
                const std::vector<T>& zero_rates);

  T GetDiscountFactorImpl(double time) const override;

  void PutOnTape() const override;

  IrDeltas GetAdjoints() const override;

 private:
  T GetZeroRate(double time) const;

  std::unique_ptr<IInterpolator<T>> interpolator_;
  std::vector<boost::gregorian::date> pillar_dates_;
  std::map<double, T> zero_rates_map_;
};
template <typename T>
ZeroRateCurve<T>::ZeroRateCurve(
    boost::gregorian::date curve_date, std::string curve_name,
    const IDayCounter& day_counter, const IInterpolator<T>& interpolator,
    std::vector<boost::gregorian::date> pillar_dates,
    const std::vector<T>& zero_rates)
    : InterestRateCurve<T>(curve_date, curve_name, day_counter),
      interpolator_(interpolator.Clone()),
      pillar_dates_(std::move(pillar_dates)) {
  std::transform(pillar_dates_.begin(), pillar_dates_.end(), zero_rates.begin(),
                 std::inserter(zero_rates_map_, zero_rates_map_.end()),
                 [&](auto date, auto zeros) {
                   return std::make_pair(
                       DateToTime(*InterestRateCurve<T>::day_counter_,
                                  InterestRateCurve<T>::curve_date_, date),
                       zeros);
                 });
}
template <typename T>
T ZeroRateCurve<T>::GetDiscountFactorImpl(double time) const {
  return T(exp(-GetZeroRate(time) * time));
}

template <typename T>
void ZeroRateCurve<T>::PutOnTape() const {}

template <>
void ZeroRateCurve<aad::a_double>::PutOnTape() const {
  for (auto& m : zero_rates_map_) {
    const_cast<aad::a_double&>(m.second).put_on_tape();
  }
}

template <typename T>
T ZeroRateCurve<T>::GetZeroRate(double time) const {
  return {interpolator_->Interpol(time, zero_rates_map_)};
}

template <typename T>
IrDeltas ZeroRateCurve<T>::GetAdjoints() const {
  return IrDeltas{};
}

template <>
inline IrDeltas ZeroRateCurve<aad::a_double>::GetAdjoints() const {
  std::vector<std::string> pillar;
  std::transform(pillar_dates_.begin(), pillar_dates_.end(),
                 std::back_inserter(pillar), [&](const auto& d) {
                   return GetCurveName() + "_" +
                          boost::gregorian::to_iso_extended_string(d);
                 });

  std::vector<double> deltas;
  std::transform(zero_rates_map_.begin(), zero_rates_map_.end(),
                 std::back_inserter(deltas),
                 [](const auto& m) { return m.second.adjoint(); });

  return IrDeltas{std::move(pillar), std::move(deltas)};
}
}  // namespace qff_a