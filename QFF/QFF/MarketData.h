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
  ~MarketData() = default;

  date getMarketDate() const;

  double getDiscountFactor(string curveName, date queryDate) const override;
  double getForwardRate(string curveName, date startDate,
                        date endDate) const override;
  double getZeroRate(string curveName, date queryDate) const override;

 private:
  date marketDate_;
  map<string, unique_ptr<IInterestRateCurve>> curveSets_;
};
}  // namespace qff
