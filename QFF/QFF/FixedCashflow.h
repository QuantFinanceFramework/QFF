#pragma once
#include "ICashflow.h"
namespace qff {
class FixedCashflow : public ICashflow {
 public:
  FixedCashflow() = default;
  FixedCashflow(double payment_amount, std::string currency_code,
                boost::gregorian::date payment_date,
                std::string discount_curve_name);
  ~FixedCashflow() = default;

  Currency Evaluate(const IMarketData& market_data,
                    const std::string& currency_code) const override;

  boost::gregorian::date GetPaymentDate() const override;

  double GetPaymentAmount(const IMarketData& market_data) const override;

 private:
  double payment_amount_;
  std::string currency_code_;
  boost::gregorian::date payment_date_;
  std::string discount_curve_name_;
};
}  // namespace qff