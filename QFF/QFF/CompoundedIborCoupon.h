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
  CompoundedIborCoupon(double notional, date paymentDate, date accrualStartDate,
                     date accrualEndDate, const IDayCounter& dayCounter,
                     const IIndex& index, double leverage, double margin);

  ~CompoundedIborCoupon() = default;

  double getPaymentAmount(const IMarketData& marketData) const override;

 private:
  double getRate(const IMarketData& marketData) const;

  double notional_;
  string currencyCode_;
  vector<date> accrual_period_dates_;
  vector<double> accrualFactors_;
  date paymentDate_;
  unique_ptr<IDayCounter> dayCounter_;
  unique_ptr<IIndex> index_;
  double leverage_;
  double margin_;
};
}  // namespace qff