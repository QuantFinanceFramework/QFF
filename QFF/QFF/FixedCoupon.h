#pragma once
#include <memory>
#include "ICashflow.h"
#include "IDayCounter.h"

namespace qff {
class FixedCoupon : public ICashflow {
 public:
  FixedCoupon() = default;
  FixedCoupon(double notional, std::string currency_code,
              boost::gregorian::date accrual_start_date,
              boost::gregorian::date accrual_end_date,
              boost::gregorian::date payment_date,
              std::string discount_curve_name, const IDayCounter& day_counter,
              double rate);

  ~FixedCoupon() = default;

  Currency Evaluate(const IMarketData& market_data,
                    const std::string& currency_code) const override;

  boost::gregorian::date GetPaymentDate() const override;

  double GetPaymentAmount(const IMarketData& market_data) const override;

 private:
  double notional_;
  std::string currency_code_;
  boost::gregorian::date accrual_start_date_;
  boost::gregorian::date accrual_end_date_;
  double accrual_factor_;
  boost::gregorian::date payment_date_;
  std::string discount_curve_name_;
  std::unique_ptr<IDayCounter> day_counter_;
  double rate_;
};
}  // namespace qff