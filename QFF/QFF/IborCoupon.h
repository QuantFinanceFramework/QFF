#pragma once
#include <memory>
#include "ICashflow.h"
#include "IIndex.h"
#include "IDayCounter.h"
#include "IMarketData.h"

namespace qff {
using std::unique_ptr;

class IborCoupon : public ICashflow {
 public:
  IborCoupon() = default;
  IborCoupon(double notional, date accrual_start_date, date accrual_end_date,
             date payment_date, const IDayCounter& day_counter,
             const IIndex& index, double leverage, double margin);

  ~IborCoupon() = default;

  double GetPaymentAmount(const IMarketData& market_data) const override;

 private:
  double GetRate(const IMarketData& market_data) const;

  double notional_;
  string currency_code_;
  date accrual_start_date_;
  date accrual_end_date_;
  double accrual_factor_;
  date payment_date_;
  unique_ptr<IDayCounter> day_counter_;
  unique_ptr<IIndex> index_;
  double leverage_;
  double margin_;
};
}  // namespace qff