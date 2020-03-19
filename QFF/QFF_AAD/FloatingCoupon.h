#pragma once
#include <memory>

#include "ICashflow.h"
#include "IDayCounter.h"
#include "IIndex.h"
#include "IPricingEnvironment.h"

namespace qff_a {
class FloatingCoupon final : public ICashflow {
 public:
  FloatingCoupon(double notional, std::string currency_code,
                 boost::gregorian::date accrual_start_date,
                 boost::gregorian::date accrual_end_date,
                 boost::gregorian::date payment_date,
                 std::string discount_curve_name,
                 const IDayCounter& day_counter, const IIndex& index,
                 double leverage, double margin);

  double GetPaymentAmount(
      const IPricingEnvironment<double>& environment) const override {
    return GetPaymentAmountImpl(environment);
  }

  aad::a_double GetPaymentAmount(
      const IPricingEnvironment<aad::a_double>& environment) const override {
    return GetPaymentAmountImpl(environment);
  }

  boost::gregorian::date GetPaymentDate() const override {
    return payment_date_;
  }

  std::string GetDiscountCurveName() const override {
    return discount_curve_name_;
  }

  std::string GetCurrencyCode() const override;

 private:
  template <typename T>
  T GetRate(const IPricingEnvironment<T>& environment) const;

  template <typename T>
  T GetPaymentAmountImpl(const IPricingEnvironment<T>& environment) const;

  double notional_{};
  std::string currency_code_;
  boost::gregorian::date accrual_start_date_;
  boost::gregorian::date accrual_end_date_;
  double accrual_factor_{};
  boost::gregorian::date payment_date_;
  std::string discount_curve_name_;
  std::unique_ptr<IDayCounter> day_counter_{};
  std::unique_ptr<IIndex> index_{};
  double leverage_{};
  double margin_{};
};

inline FloatingCoupon::FloatingCoupon(double notional,
                                      std::string currency_code,
                                      boost::gregorian::date accrual_start_date,
                                      boost::gregorian::date accrual_end_date,
                                      boost::gregorian::date payment_date,
                                      std::string discount_curve_name,
                                      const IDayCounter& day_counter,
                                      const IIndex& index, double leverage,
                                      double margin)
    : notional_(notional),
      currency_code_(std::move(currency_code)),
      accrual_start_date_(accrual_start_date),
      accrual_end_date_(accrual_end_date),
      accrual_factor_(day_counter.CalculateYearFraction(accrual_start_date,
                                                        accrual_end_date)),
      payment_date_(payment_date),
      discount_curve_name_(std::move(discount_curve_name)),
      day_counter_(day_counter.Clone()),
      index_(index.Clone()),
      leverage_(leverage),
      margin_(margin) {}

inline std::string FloatingCoupon::GetCurrencyCode() const {
  return currency_code_;
}

template <typename T>
T FloatingCoupon::GetRate(const IPricingEnvironment<T>& environment) const {
  return T(leverage_ * index_->GetRate(accrual_start_date_, accrual_end_date_,
                                       environment) +
           margin_);
}
template <typename T>
T FloatingCoupon::GetPaymentAmountImpl(
    const IPricingEnvironment<T>& environment) const {
  return T(notional_ * GetRate(environment) * accrual_factor_);
}
}  // namespace qff_a