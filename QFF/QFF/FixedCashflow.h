#pragma once
#include "ICashflow.h"
namespace qff {
class FixedCashflow : public ICashflow {
 public:
  FixedCashflow() = default;
  FixedCashflow(double payment_amount, string currency_code, date payment_date);
  ~FixedCashflow() = default;

  date GetPaymentDate() const override;
  double GetPaymentAmount(const IMarketData& market_data) const override;

 private:
  double payment_amount_;
  string currency_code_;
  date payment_date_;
};
}  // namespace qff