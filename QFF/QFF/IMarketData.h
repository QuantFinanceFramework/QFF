#pragma once
#include <boost/date_time/gregorian/gregorian.hpp>
#include <string>

namespace qff {
using boost::gregorian::date;
using std::string;

class IMarketData {
 public:
  IMarketData() = default;
  virtual ~IMarketData() = default;

  virtual date getMarketDate() const = 0;

  virtual double getDiscountFactor(const string& curveName,
                                   const date& queryDate) const = 0;

  virtual double getForwardRate(const string& curveName, const date& startDate,
                                const date& endDate) const = 0;

  virtual double getZeroRate(const string& curveName,
                             const date& queryDate) const = 0;

  virtual double getPastFixing(const string& curveName,
                               const date& queryDate) const = 0;
};
}  // namespace qff
