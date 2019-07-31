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

class CompoundedOvernightCoupon : public ICashflow {
 public:
  CompoundedOvernightCoupon() = default;
  CompoundedOvernightCoupon(double notional, string currency_code,
                            vector<date> accrual_period_dates,
                            date payment_date, string discount_curve_name,
                            const IDayCounter& day_counter, const IIndex& index,
                            double leverage, double margin,
                            Period rate_cut_off);

  ~CompoundedOvernightCoupon() = default;

  Currency Evaluate(const IMarketData& market_data,
                    const string& currency_code) const override;

  date GetPaymentDate() const override;

  double GetPaymentAmount(const IMarketData& market_data) const override;

 private:
  double GetRate(const IMarketData& market_data) const;

  double notional_{};
  string currency_code_;
  vector<date> accrual_period_dates_;
  vector<double> accrual_factors_;
  date payment_date_;
  string discount_curve_name_;
  unique_ptr<IDayCounter> day_counter_;
  unique_ptr<IIndex> index_;
  double leverage_{};
  double margin_{};
  Period rate_cut_off_{};
};
}  // namespace qff