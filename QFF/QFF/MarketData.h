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

  date getMarketDate() const override;

  double getDiscountFactor(const string& curveName,
                           const date& queryDate) const override;

  double getForwardRate(const string& curveName, const date& startDate,
                        const date& endDate) const override;

  double getZeroRate(const string& curveName,
                     const date& queryDate) const override;

  double getPastFixing(const string& curveName,
                       const date& queryDate) const override;
 
 private:
  date marketDate_;
  map<string, unique_ptr<IInterestRateCurve>> curveSets_;

};
}  // namespace qff
