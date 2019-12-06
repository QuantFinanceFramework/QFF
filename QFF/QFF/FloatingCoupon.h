#pragma once
#include <memory>
#include "ICashflow.h"
#include "IDayCounter.h"
#include "IIndex.h"
#include "IMarketData.h"

namespace qff {

class FloatingCoupon : public ICashflow {
 public:
  FloatingCoupon() = default;
  FloatingCoupon(double notional, std::string currency_code,
                 boost::gregorian::date accrual_start_date,
                 boost::gregorian::date accrual_end_date,
                 boost::gregorian::date payment_date,
             std::string discount_curve_name, const IDayCounter& day_counter,
             const IIndex& index, double leverage, double margin);

  Currency Evaluate(const IMarketData& market_data,
                    const std::string& currency_code) const override;

  double GetPaymentAmount(const IMarketData& market_data) const override;

  boost::gregorian::date GetPaymentDate() const override;

 private:
  double GetRate(const IMarketData& market_data) const;

  double notional_;
  std::string currency_code_;
  boost::gregorian::date accrual_start_date_;
  boost::gregorian::date accrual_end_date_;
  double accrual_factor_;
  boost::gregorian::date payment_date_;
  std::string discount_curve_name_;
  std::unique_ptr<IDayCounter> day_counter_;
  std::unique_ptr<IIndex> index_;
  double leverage_;
  double margin_;
};
}  // namespace qff