#pragma once
#include <memory>

#include "DateFunctions.h"
#include "IDayCounter.h"
#include "IInterestRateCurve.h"

namespace qff_a {
template <typename T>
class InterestRateCurve : public IInterestRateCurve<T> {
 public:
  InterestRateCurve(boost::gregorian::date curve_date, std::string curve_name,
                    const IDayCounter& day_counter);

  T GetDiscountFactor(
      const boost::gregorian::date& query_date) const override final {
    return GetDiscountFactorImpl(ToTime(query_date));
  }

  boost::gregorian::date GetCurveDate() const;

  std::string GetCurveName() const;

 protected:
  virtual T GetDiscountFactorImpl(double time) const = 0;
  double ToTime(const boost::gregorian::date& query_date) const;

  boost::gregorian::date curve_date_;
  std::string curve_name_;
  std::unique_ptr<IDayCounter> day_counter_;
};

template <typename T>
InterestRateCurve<T>::InterestRateCurve(boost::gregorian::date curve_date,
                                        std::string curve_name,
                                        const IDayCounter& day_counter)
    : curve_date_(std::move(curve_date)),
      curve_name_(std::move(curve_name)),
      day_counter_(day_counter.Clone()) {}

template <typename T>
boost::gregorian::date InterestRateCurve<T>::GetCurveDate() const {
  return curve_date_;
}

template <typename T>
std::string InterestRateCurve<T>::GetCurveName() const {
  return curve_name_;
}

template <typename T>
double InterestRateCurve<T>::ToTime(
    const boost::gregorian::date& query_date) const {
  return DateToTime(*day_counter_, curve_date_, query_date);
}
}  // namespace qff_a