#pragma once
#include <algorithm>
#include "../AAD/aad_all.h"
#include "IInterpolator.h"
#include "InterestRateCurve.h"

namespace qff_a {
template <typename T>
class DiscountFactorsCurve final : public InterestRateCurve<T> {
 public:
  DiscountFactorsCurve(boost::gregorian::date curve_date,
                       const IDayCounter& day_counter,
                       const IInterpolator<T>& interpolator,
                       std::vector<boost::gregorian::date> dates,
                       const std::vector<T>& discount_factors);

 private:
  T GetDiscountFactorImpl(double time) const final;
  std::vector<double> GetAdjointsImpl() const final;

  std::unique_ptr<IInterpolator<T>> interpolator_;
  std::vector<boost::gregorian::date> dates_;
  std::map<double, T> discount_factors_map_;
};

template <typename T>
DiscountFactorsCurve<T>::DiscountFactorsCurve(
    boost::gregorian::date curve_date, const IDayCounter& day_counter,
    const IInterpolator<T>& interpolator,
    std::vector<boost::gregorian::date> dates,
    const std::vector<T>& discount_factors)
    : InterestRateCurve<T>(curve_date, day_counter),
      interpolator_(interpolator.Clone()),
      dates_(std::move(dates)) {
  std::transform(
      dates_.begin(), dates_.end(), discount_factors.begin(),
      std::inserter(discount_factors_map_, discount_factors_map_.end()),
      [&](auto date, auto discount_factor) {
        return std::make_pair(
            DateToTime(*InterestRateCurve<T>::day_counter_,
                       InterestRateCurve<T>::curve_date_, date),
            discount_factor);
      });
}

template <typename T>
T DiscountFactorsCurve<T>::GetDiscountFactorImpl(double time) const {
  return {interpolator_->Interpol(time, discount_factors_map_)};
}

template <typename T>
std::vector<double> DiscountFactorsCurve<T>::GetAdjointsImpl() const {
  return std::vector<double>(size(dates_));
}

template <>
inline std::vector<double>
DiscountFactorsCurve<aad::a_double>::GetAdjointsImpl() const {
  std::vector<double> adjoints(size(dates_));
  std::transform(discount_factors_map_.begin(), discount_factors_map_.end(),
                 adjoints.begin(),
                 [](const auto& itr) { return itr.second.adjoint(); });
  return adjoints;
}
}  // namespace qff_a