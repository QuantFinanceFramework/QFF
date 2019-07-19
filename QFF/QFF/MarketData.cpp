#include "MarketData.h"

namespace qff {
date MarketData::getMarketDate() const { return marketDate_; }

double MarketData::getDiscountFactor(string curveName, date queryDate) const {
  return 0.0;
}

double MarketData::getForwardRate(string curveName, date startDate,
                                  date endDate) const {
  return 0.0;
}

double MarketData::getZeroRate(string curveName, date queryDate) const {
  return 0.0;
}
}  // namespace qff