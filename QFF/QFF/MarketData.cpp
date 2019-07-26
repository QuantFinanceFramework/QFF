#include "MarketData.h"

namespace qff {
MarketData::MarketData(date market_date,
                       map<string, unique_ptr<IInterestRateCurve>> curve_set,
                       map<string, map<date, double>> past_fixing_set)
    : market_date_(market_date),
      curve_set_(std::move(curve_set)),
      past_fixing_set_(std::move(past_fixing_set)) {}

date MarketData::GetMarketDate() const { return market_date_; }

double MarketData::GetDiscountFactor(const string& curve_name,
                                     const date& query_date) const {
  const auto curve_itr = curve_set_.find(curve_name);
  return curve_itr->second->GetDiscountFactor(query_date);
}

double MarketData::GetForwardRate(const string& curve_name,
                                  const date& start_date,
                                  const date& end_date) const {
  return 0.0;
}

double MarketData::GetZeroRate(const string& curve_name,
                               const date& query_date) const {
  return 0.0;
}

double MarketData::GetPastFixing(const string& curve_name,
                                 const date& query_date) const {
  const auto curve_itr = past_fixing_set_.find(curve_name);
  return curve_itr->second.find(query_date)->second;
}
}  // namespace qff