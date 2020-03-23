#pragma once
#include <map>
#include <memory>
#include <stdexcept>

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
      std::map<std::string, std::unique_ptr<ICreditCurve<T>>> credit_curves_set,
      std::map<std::string, T> fx_today_map);

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

  T GetFxToday(std::string base_currency,
               std::string quote_currency) const override;

 private:
  boost::gregorian::date pricing_date_;
  std::map<std::string, std::unique_ptr<IInterestRateCurve<T>>>
      rate_curves_set_;
  std::map<std::string, std::map<boost::gregorian::date, double>>
      past_rate_fixing_set_;
  std::map<std::string, std::unique_ptr<ICreditCurve<T>>> credit_curves_set_;
  std::map<std::string, T> fx_today_map_;
};

template <typename T>
PricingEnvironment<T>::PricingEnvironment(
    boost::gregorian::date pricing_date,
    std::map<std::string, std::unique_ptr<IInterestRateCurve<T>>>
        rate_curves_set,
    std::map<std::string, std::map<boost::gregorian::date, double>>
        past_rate_fixing_set,
    std::map<std::string, std::unique_ptr<ICreditCurve<T>>> credit_curves_set,
    std::map<std::string, T> fx_today_map)
    : pricing_date_(pricing_date),
      rate_curves_set_(std::move(rate_curves_set)),
      past_rate_fixing_set_(std::move(past_rate_fixing_set)),
      credit_curves_set_(std::move(credit_curves_set)),
      fx_today_map_(std::move(fx_today_map)) {}

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
  if (curve_itr == past_rate_fixing_set_.end()) {
    throw std::logic_error{"Rate history is not past rate fixing set"};
  }
  const auto past_fixing_itr = curve_itr->second.find(query_date);
  if (past_fixing_itr == curve_itr->second.end()) {
    throw std::logic_error{"Past fixing cannot be found"};
  }
  return past_fixing_itr->second;
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

template <typename T>
T PricingEnvironment<T>::GetFxToday(std::string base_currency,
                                    std::string quote_currency) const {
  if (base_currency == quote_currency) return T(1.0);

  const auto fx_itr = fx_today_map_.find(base_currency + quote_currency);
  if (fx_itr != fx_today_map_.end()) {
    return fx_itr->second;
  }

  const auto inverse_fx_itr =
      fx_today_map_.find(quote_currency + base_currency);
  if (inverse_fx_itr != fx_today_map_.end()) {
    return T(1.0 / inverse_fx_itr->second);
  }

  throw std::logic_error{"FX today rate cannot be found"};
}
}  // namespace qff_a