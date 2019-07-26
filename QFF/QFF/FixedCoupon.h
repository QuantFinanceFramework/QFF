#pragma once
#include <memory>
#include "ICashflow.h"
#include "IDayCounter.h"

namespace qff {
class FixedCoupon : public ICashflow {
 public:
  FixedCoupon() = default;
  FixedCoupon(double notional, date accrual_start_date, date accrual_end_date,
              date payment_date, const IDayCounter& day_counter, double rate);

  ~FixedCoupon() = default;

  double GetPaymentAmount(const IMarketData& market_data) const override;

 private:
  double notional_;
  string currency_code_;
  date accrual_start_date_;
  date accrual_end_date_;
  double accrual_factor_;
  date payment_date_;
  unique_ptr<IDayCounter> day_counter_;
  double rate_;
};
}  // namespace qff