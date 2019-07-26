#pragma once
#include <memory>
#include <vector>
#include "ICashflow.h"
#include "IDayCounter.h"
#include "IIndex.h"
#include "IMarketData.h"
#include "Period.h"

namespace qff {
using std::unique_ptr;
using std::vector;

class AveragedOvernightCoupon : public ICashflow {
 public:
  AveragedOvernightCoupon() = default;
  AveragedOvernightCoupon(double notional, string currency_code,
                          vector<date> accrual_period_dates, date payment_date,
                          const IDayCounter& day_counter, const IIndex& index,
                          double leverage, double margin, Period rate_cut_off);

  ~AveragedOvernightCoupon() = default;

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
  Period rate_cut_off_;
};
}  // namespace qff