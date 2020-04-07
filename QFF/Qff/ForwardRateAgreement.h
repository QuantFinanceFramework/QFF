#pragma once
#include <utility>

#include "IDayCounter.h"
#include "IIndex.h"
#include "IProduct.h"
namespace qff_a {
class ForwardRateAgreement final : public IProduct {
 public:
  ForwardRateAgreement(double notional, std::string currency_code,
                       boost::gregorian::date accrual_start_date,
                       boost::gregorian::date accrual_end_date,
                       boost::gregorian::date payment_date,
                       std::string discount_curve_name,
                       std::unique_ptr<IDayCounter> day_counter, double strike,
                       std::unique_ptr<IIndex> index, double leverage,
                       double margin);

  ForwardRateAgreement(double notional, std::string currency_code,
                       boost::gregorian::date accrual_start_date,
                       boost::gregorian::date accrual_end_date,
                       boost::gregorian::date payment_date,
                       std::string discount_curve_name,
                       const IDayCounter& day_counter, double strike,
                       const IIndex& index, double leverage, double margin);

  Currency<double> Evaluate(
      const IPricingEnvironment<double>& environment,
      const std::string& valuation_currency) const override {
    return EvaluateImpl(environment, valuation_currency);
  }

  Currency<aad::a_double> Evaluate(
      const IPricingEnvironment<aad::a_double>& environment,
      const std::string& valuation_currency) const override {
    return EvaluateImpl(environment, valuation_currency);
  }

 private:
  template <typename T>
  Currency<T> EvaluateImpl(const IPricingEnvironment<T>& environment,
                           const std::string& valuation_currency) const;

  template <typename T>
  T GetRate(const IPricingEnvironment<T>& environment) const;

  template <typename T>
  bool IsExpired(const IPricingEnvironment<T>& environment) const;

  double notional_{};
  std::string currency_code_;
  boost::gregorian::date accrual_start_date_;
  boost::gregorian::date accrual_end_date_;
  boost::gregorian::date payment_date_;
  std::string discount_curve_name_;
  std::unique_ptr<IDayCounter> day_counter_;
  double strike_{};
  std::unique_ptr<IIndex> index_{};
  double leverage_{};
  double margin_{};
};

inline ForwardRateAgreement::ForwardRateAgreement(
    double notional, std::string currency_code,
    boost::gregorian::date accrual_start_date,
    boost::gregorian::date accrual_end_date,
    boost::gregorian::date payment_date, std::string discount_curve_name,
    std::unique_ptr<IDayCounter> day_counter, double strike,
    std::unique_ptr<IIndex> index, double leverage, double margin)
    : notional_{notional},
      currency_code_{std::move(currency_code)},
      accrual_start_date_{accrual_start_date},
      accrual_end_date_{accrual_end_date},
      payment_date_{payment_date},
      discount_curve_name_{std::move(discount_curve_name)},
      day_counter_{std::move(day_counter)},
      strike_{strike},
      index_{std::move(index)},
      leverage_{leverage},
      margin_{margin} {}

inline ForwardRateAgreement::ForwardRateAgreement(
    double notional, std::string currency_code,
    boost::gregorian::date accrual_start_date,
    boost::gregorian::date accrual_end_date,
    boost::gregorian::date payment_date, std::string discount_curve_name,
    const IDayCounter& day_counter, double strike, const IIndex& index,
    double leverage, double margin)
    : notional_{notional},
      currency_code_{std::move(currency_code)},
      accrual_start_date_{accrual_start_date},
      accrual_end_date_{accrual_end_date},
      payment_date_{payment_date},
      discount_curve_name_{std::move(discount_curve_name)},
      day_counter_{day_counter.Clone()},
      strike_{strike},
      index_{index.Clone()},
      leverage_{leverage},
      margin_{margin} {}

template <typename T>
Currency<T> ForwardRateAgreement::EvaluateImpl(
    const IPricingEnvironment<T>& environment,
    const std::string& valuation_currency) const {
  if (IsExpired(environment)) {
    return Currency(valuation_currency, T(0.0));
  }
  auto accrual_factor = day_counter_->CalculateYearFraction(accrual_start_date_,
                                                            accrual_end_date_);
  auto total_rate = GetRate(environment) + margin_;

  auto npv =
      notional_ *
      environment.GetDiscountFactor(discount_curve_name_, payment_date_) *
      (1 - (1 + strike_ * accrual_factor) / (1 + total_rate * accrual_factor));

  return Currency(valuation_currency, T(npv));
}

template <typename T>
T ForwardRateAgreement::GetRate(
    const IPricingEnvironment<T>& environment) const {
  return T(leverage_ * index_->GetRate(accrual_start_date_, accrual_end_date_,
                                       environment));
}

template <typename T>
bool ForwardRateAgreement::IsExpired(
    const IPricingEnvironment<T>& environment) const {
  if (payment_date_ < environment.GetPricingDate()) {
    return true;
  }
  return false;
}
}  // namespace qff_a