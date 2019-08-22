#pragma once
#include "IProduct.h"
namespace qff {
class CdsProtection : public IProduct {
 public:
  CdsProtection() = default;
  CdsProtection(double notional, std::string currency_code,
                boost::gregorian::date start_date,
                boost::gregorian::date end_date, std::string discount_curve_name,
                std::string survival_curve_name, double recovery_rate);
  ~CdsProtection() = default;

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
};
}  // namespace qff