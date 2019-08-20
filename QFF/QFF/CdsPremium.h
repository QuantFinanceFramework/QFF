#pragma once
#include <memory>
#include "ICashflow.h"
#include "IDayCounter.h"

namespace qff {
class CdsPremium : public ICashflow {
 public:
  CdsPremium() = default;
  CdsPremium(double notional, string currency_code, date accrual_start_date,
             date accrual_end_date, date payment_date,
             string discount_curve_name, string survival_curve_name,
             const IDayCounter& day_counter, double cds_spread);

  ~CdsPremium() = default;

  Currency Evaluate(const IMarketData& market_data,
                    const string& currency_code) const override;

  date GetPaymentDate() const override;

  double GetPaymentAmount(const IMarketData& market_data) const override;

 private:
  double notional_;
  string currency_code_;
  date accrual_start_date_;
  date accrual_end_date_;
  double accrual_factor_;
  date payment_date_;
  string discount_curve_name_;
  string survival_curve_name_;
  unique_ptr<IDayCounter> day_counter_;
  double cds_spread_;
};
}  // namespace qff