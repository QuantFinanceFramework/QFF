#pragma once
#include <map>
#include <memory>
#include "ICreditCurve.h"
#include "IInterestRateCurve.h"
#include "IMarketData.h"

namespace qff {

class MarketData : public IMarketData {
 public:
  MarketData() = default;
  MarketData(
      boost::gregorian::date market_date,
      std::map<std::string, std::unique_ptr<IInterestRateCurve>> curve_set,
      std::map<std::string, std::unique_ptr<ICreditCurve>> credit_curve_set,
      std::map<std::string, std::map<boost::gregorian::date, double>>
          past_fixing_set);

  boost::gregorian::date GetMarketDate() const override;

  double GetDiscountFactor(
      const std::string& curve_name,
      const boost::gregorian::date& query_date) const override;

  double GetSurvivalProbability(
      const std::string& curve_name,
      const boost::gregorian::date& query_date) const override;

  double GetPastFixing(const std::string& curve_name,
                       const boost::gregorian::date& query_date) const override;

 private:
  boost::gregorian::date market_date_;
  std::map<std::string, std::unique_ptr<IInterestRateCurve>> curve_set_;
  std::map<std::string, std::unique_ptr<ICreditCurve>> credit_curve_set_;
  std::map<std::string, std::map<boost::gregorian::date, double>>
      past_fixing_set_;
};
}  // namespace qff
