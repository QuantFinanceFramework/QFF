#pragma once
#include <map>
#include <memory>

#include "IInterestRateCurve.h"
#include "IPricingEnvironment.h"

namespace qff_a {
template <typename T>
class PricingEnvironment final : public IPricingEnvironment<T> {
 public:
  PricingEnvironment(
      boost::gregorian::date pricing_date,
      std::map<std::string, std::unique_ptr<IInterestRateCurve<T>>>
          rate_curves_set,
      std::map<std::string, std::map<boost::gregorian::date, double>>
          past_rate_fixing_set);

  boost::gregorian::date GetPricingDate() const final;

  T GetDiscountFactor(const std::string& curve_name,
                      const boost::gregorian::date& query_date) const final;

  double GetPastRateFixing(
      const std::string& curve_name,
      const boost::gregorian::date& query_date) const final;

 private:
  boost::gregorian::date pricing_date_;
  std::map<std::string, std::unique_ptr<IInterestRateCurve<T>>>
      rate_curves_set_;
  std::map<std::string, std::map<boost::gregorian::date, double>>
      past_rate_fixing_set_;
};

template <typename T>
PricingEnvironment<T>::PricingEnvironment(
    boost::gregorian::date pricing_date,
    std::map<std::string, std::unique_ptr<IInterestRateCurve<T>>>
        rate_curves_set,
    std::map<std::string, std::map<boost::gregorian::date, double>>
        past_rate_fixing_set)
    : pricing_date_(pricing_date),
      rate_curves_set_(std::move(rate_curves_set)),
      past_rate_fixing_set_(std::move(past_rate_fixing_set)) {}

template <typename T>
boost::gregorian::date PricingEnvironment<T>::GetPricingDate() const {
  return pricing_date_;
}

template <typename T>
T PricingEnvironment<T>::GetDiscountFactor(
    const std::string& curve_name,
    const boost::gregorian::date& query_date) const {
  const auto curve_itr = rate_curves_set_.find(curve_name);
  return curve_itr->second->GetDiscountFactor(query_date);
}

template <typename T>
double PricingEnvironment<T>::GetPastRateFixing(
    const std::string& curve_name,
    const boost::gregorian::date& query_date) const {
  const auto curve_itr = past_rate_fixing_set_.find(curve_name);
  return curve_itr->second.find(query_date)->second;
}
}  // namespace qff_a