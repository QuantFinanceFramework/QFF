#pragma once
#include <map>
#include <memory>

#include "ICreditCurve.h"
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
          past_rate_fixing_set,
      std::map<std::string, std::unique_ptr<ICreditCurve<T>>>
          credit_curves_set);

  boost::gregorian::date GetPricingDate() const override;

  T GetDiscountFactor(const std::string& curve_name,
                      const boost::gregorian::date& query_date) const override;

  double GetPastRateFixing(
      const std::string& curve_name,
      const boost::gregorian::date& query_date) const override;

  void PutInterestRateCurvesOnTape() const override;

  IrDeltas GetInterestRateAdjoints() const override;

  IrDeltas GetInterestRateAdjoints(
      const std::string& curve_name) const override;

  T GetSurvivalProbability(
      const std::string& curve_name,
      const boost::gregorian::date& query_date) const override;

  std::vector<double> GetCreditAdjoints(
      const std::string& curve_name) const override;

 private:
  boost::gregorian::date pricing_date_;
  std::map<std::string, std::unique_ptr<IInterestRateCurve<T>>>
      rate_curves_set_;
  std::map<std::string, std::map<boost::gregorian::date, double>>
      past_rate_fixing_set_;
  std::map<std::string, std::unique_ptr<ICreditCurve<T>>> credit_curves_set_;
};

template <typename T>
PricingEnvironment<T>::PricingEnvironment(
    boost::gregorian::date pricing_date,
    std::map<std::string, std::unique_ptr<IInterestRateCurve<T>>>
        rate_curves_set,
    std::map<std::string, std::map<boost::gregorian::date, double>>
        past_rate_fixing_set,
    std::map<std::string, std::unique_ptr<ICreditCurve<T>>> credit_curves_set)
    : pricing_date_(pricing_date),
      rate_curves_set_(std::move(rate_curves_set)),
      past_rate_fixing_set_(std::move(past_rate_fixing_set)),
      credit_curves_set_(std::move(credit_curves_set)) {}

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

template <typename T>
void PricingEnvironment<T>::PutInterestRateCurvesOnTape() const {
  for (auto& m : rate_curves_set_) {
    m.second->PutOnTape();
  }
}

template <typename T>
IrDeltas PricingEnvironment<T>::GetInterestRateAdjoints() const {
  IrDeltas result;
  for (const auto& s : rate_curves_set_) {
    result.Append(s.second->GetAdjoints());
  }
  return result;
}

template <typename T>
IrDeltas PricingEnvironment<T>::GetInterestRateAdjoints(
    const std::string& curve_name) const {
  const auto curve_itr = rate_curves_set_.find(curve_name);
  return curve_itr->second->GetAdjoints();
}

template <typename T>
T PricingEnvironment<T>::GetSurvivalProbability(
    const std::string& curve_name,
    const boost::gregorian::date& query_date) const {
  const auto curve_itr = credit_curves_set_.find(curve_name);
  return curve_itr->second->GetSurvivalProbability(query_date);
}

template <typename T>
std::vector<double> PricingEnvironment<T>::GetCreditAdjoints(
    const std::string& curve_name) const {
  const auto curve_itr = credit_curves_set_.find(curve_name);
  return curve_itr->second->GetAdjoints();
}
}  // namespace qff_a