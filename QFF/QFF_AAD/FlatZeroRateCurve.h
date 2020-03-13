#pragma once
#include "../AAD/aad_all.h"
#include "InterestRateCurve.h"

namespace qff_a {
template <typename T>
class FlatZeroRateCurve final : public InterestRateCurve<T> {
 public:
  FlatZeroRateCurve(boost::gregorian::date curve_date, std::string curve_name,
                    const IDayCounter& day_counter, T zero_rate);

  T GetDiscountFactorImpl(double time) const override;

  void PutOnTape() const override;

  IrDeltas GetAdjoints() const override;

 private:
  T GetZeroRate(double time) const;

  T zero_rate_;
};

template <typename T>
FlatZeroRateCurve<T>::FlatZeroRateCurve(boost::gregorian::date curve_date,
                                        std::string curve_name,
                                        const IDayCounter& day_counter,
                                        T zero_rate)
    : InterestRateCurve<T>(curve_date, curve_name, day_counter),
      zero_rate_(zero_rate) {}

template <typename T>
T FlatZeroRateCurve<T>::GetDiscountFactorImpl(double time) const {
  return T(exp(-GetZeroRate(time) * time));
}

template <typename T>
void FlatZeroRateCurve<T>::PutOnTape() const {}

template <>
inline void FlatZeroRateCurve<aad::a_double>::PutOnTape() const {
  const_cast<aad::a_double&>(zero_rate_).put_on_tape();
}

template <typename T>
IrDeltas FlatZeroRateCurve<T>::GetAdjoints() const {
  return IrDeltas{};
}

template <>
inline IrDeltas FlatZeroRateCurve<aad::a_double>::GetAdjoints() const {
  return IrDeltas{{GetCurveName() + "_" + "Total"}, {zero_rate_.adjoint()}};
}
template <typename T>
T FlatZeroRateCurve<T>::GetZeroRate(double time) const {
  return zero_rate_;
}
}  // namespace qff_a
