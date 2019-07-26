#include "MarketData.h"

namespace qff {
date MarketData::GetMarketDate() const { return market_date_; }

double MarketData::GetDiscountFactor(const string& curve_name,
                                     const date& query_date) const {
  return 0.0;
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
  return 0.0;
}
}  // namespace qff