#pragma once
#include "boost/date_time/gregorian/gregorian.hpp"
#include "IMarketData.h"
#include <memory>

namespace qff {
using boost::gregorian::date;
using std::unique_ptr;

class IIndex {
 public:
  IIndex() = default;
  virtual ~IIndex() = default;

  virtual unique_ptr<IIndex> Clone() const = 0;

  virtual double GetRate(const date& start_date, const IMarketData& market_data) const = 0;
  virtual date GetFixingDate(const date& start_date) const = 0;
};
}  // namespace qff