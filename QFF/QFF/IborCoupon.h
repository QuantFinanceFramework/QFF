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
  IborCoupon(double notional, date accrualStartDate, date accrualEndDate,
             date paymentDate, const IDayCounter& dayCounter,
             const IIndex& index, double leverage, double margin);

  ~IborCoupon() = default;

  double getPaymentAmount(const IMarketData& marketData) const override;

 private:
  double getRate(const IMarketData& marketData) const;

  double notional_;
  string currencyCode_;
  date accrualStartDate_;
  date accrualEndDate_;
  double accrualFactor_;
  date paymentDate_;
  unique_ptr<IDayCounter> dayCounter_;
  unique_ptr<IIndex> index_;
  double leverage_;
  double margin_;
};
}  // namespace qff