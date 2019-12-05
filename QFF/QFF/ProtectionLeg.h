#pragma once
#include <vector>
#include "IProduct.h"
#include "SwapScheduler.h"

namespace qff {
class ProtectionLeg : public IProduct {
 public:
  ProtectionLeg() = default;
  ProtectionLeg(double notional, std::string currency_code,
             boost::gregorian::date start_date, boost::gregorian::date end_date,
             std::string discount_curve_name, std::string survival_curve_name,
             double recovery_rate, Frequency estimation_frequency);

  Currency Evaluate(const IMarketData& market_data,
                    const std::string& currency_code) const override;

 private:
  double notional_;
  std::string currency_code_;
  boost::gregorian::date start_date_;
  boost::gregorian::date end_date_;
  std::string discount_curve_name_;
  std::string survival_curve_name_;
  double recovery_rate_;
  Frequency estimation_frequency_;
  mutable std::vector<boost::gregorian::date> estimation_schedule_;
};
}  // namespace qff