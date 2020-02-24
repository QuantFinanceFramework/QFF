#pragma once
#include <memory>

#include "DateFunctions.h"
#include "IDayCounter.h"
#include "IInterestRateCurve.h"

namespace qff_a {
template <typename T>
class InterestRateCurve : public IInterestRateCurve<T> {
 public:
  InterestRateCurve(boost::gregorian::date curve_date,
                    const IDayCounter& day_counter);

  boost::gregorian::date GetCurveDate() const;

 protected:
  double ToTime(const boost::gregorian::date& query_date) const;

  boost::gregorian::date curve_date_;
  std::unique_ptr<IDayCounter> day_counter_;

 private:
  T GetDiscountFactorImpl(const boost::gregorian::date& query_date) const final;
};

template <typename T>
InterestRateCurve<T>::InterestRateCurve(boost::gregorian::date curve_date,
                                        const IDayCounter& day_counter)
    : curve_date_(std::move(curve_date)), day_counter_(day_counter.Clone()) {}

template <typename T>
boost::gregorian::date InterestRateCurve<T>::GetCurveDate() const {
  return curve_date_;
}

template <typename T>
double InterestRateCurve<T>::ToTime(
    const boost::gregorian::date& query_date) const {
  return DateToTime(*day_counter_, curve_date_, query_date);
}

template <typename T>
T InterestRateCurve<T>::GetDiscountFactorImpl(
    const boost::gregorian::date& query_date) const {
  return IInterestRateCurve<T>::GetDiscountFactor(ToTime(query_date));
}
}  // namespace qff_a