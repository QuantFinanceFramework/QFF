#include "MarketData.h"

namespace qff {
date MarketData::getMarketDate() const { return marketDate_; }

double MarketData::getDiscountFactor(const string& curveName,
                                     const date& queryDate) const {
  return 0.0;
}

double MarketData::getForwardRate(const string& curveName,
                                  const date& startDate,
                                  const date& endDate) const {
  return 0.0;
}

double MarketData::getZeroRate(const string& curveName,
                               const date& queryDate) const {
  return 0.0;
}

double MarketData::getPastFixing(const string& curveName,
                                 const date& queryDate) const {
  return 0.0;
}
}  // namespace qff