#pragma once
#include <memory>
#include "ICashflow.h"
#include "IIndex.h"
#include "IDayCounter.h"
#include "IMarketData.h"
#include <vector>

namespace qff {
using std::unique_ptr;
using std::vector;

class CompoundedIborCoupon : public ICashflow {
 public:
  CompoundedIborCoupon() = default;
  CompoundedIborCoupon(double notional, date payment_date, date accrual_start_date,
                     date accrual_end_date, const IDayCounter& day_counter,
                     const IIndex& index, double leverage, double margin);

  ~CompoundedIborCoupon() = default;

  double GetPaymentAmount(const IMarketData& market_data) const override;

 private:
  static double GetRate(const IMarketData& market_data);

  double notional_;
  string currency_code_;
  vector<date> accrual_period_dates_;
  vector<double> accrual_factors_;
  date payment_date_;
  unique_ptr<IDayCounter> day_counter_;
  unique_ptr<IIndex> index_;
  double leverage_;
  double margin_;
};
}  // namespace qff