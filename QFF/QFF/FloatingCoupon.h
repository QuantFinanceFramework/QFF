#pragma once
#include <memory>
#include "ICashflow.h"
#include "IDayCounter.h"
#include "IIndex.h"
#include "IMarketData.h"

namespace qff {
using std::unique_ptr;

class FloatingCoupon : public ICashflow {
 public:
  FloatingCoupon() = default;
  FloatingCoupon(double notional, string currency_code, date accrual_start_date,
             date accrual_end_date, date payment_date,
             string discount_curve_name, const IDayCounter& day_counter,
             const IIndex& index, double leverage, double margin);

  ~FloatingCoupon() = default;

  Currency Evaluate(const IMarketData& market_data,
                    const string& currency_code) const override;

  double GetPaymentAmount(const IMarketData& market_data) const override;

  date GetPaymentDate() const override;

 private:
  double GetRate(const IMarketData& market_data) const;

  double notional_{};
  string currency_code_;
  date accrual_start_date_;
  date accrual_end_date_;
  double accrual_factor_{};
  date payment_date_;
  string discount_curve_name_;
  unique_ptr<IDayCounter> day_counter_;
  unique_ptr<IIndex> index_;
  double leverage_{};
  double margin_{};
};
}  // namespace qff