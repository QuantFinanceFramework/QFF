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
  CompoundedOvernightCoupon(double notional, date paymentDate,
                            date accrualStartDate, date accrualEndDate,
                            const IDayCounter& dayCounter, const IIndex& index,
                            Period rate_cut_off, double leverage,
                            double margin);

  ~CompoundedOvernightCoupon() = default;

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
  Period rate_cut_off_;
  double leverage_;
  double margin_;
};
}  // namespace qff