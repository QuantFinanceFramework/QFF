#pragma once
#include <map>
#include <memory>
#include "IInterestRateCurve.h"
#include "IMarketData.h"

namespace qff {
using std::map;
using std::unique_ptr;

class MarketData : public IMarketData {
 public:
  MarketData() = default;
  MarketData(date market_date,
             map<string, unique_ptr<IInterestRateCurve>> curve_set,
             map<string, map<date, double>> past_fixing_set);

  ~MarketData() = default;

  date GetMarketDate() const override;

  double GetDiscountFactor(const string& curve_name,
                           const date& query_date) const override;

  double GetForwardRate(const string& curve_name, const date& start_date,
                        const date& end_date) const override;

  double GetZeroRate(const string& curve_name,
                     const date& query_date) const override;

  double GetPastFixing(const string& curve_name,
                       const date& query_date) const override;

 private:
  date market_date_;
  map<string, unique_ptr<IInterestRateCurve>> curve_set_;
  map<string, map<date, double>> past_fixing_set_;
};
}  // namespace qff
