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

  virtual unique_ptr<IIndex> clone() const = 0;

  virtual double getRate(const date& startDate, const IMarketData& marketData) const = 0;
};
}  // namespace qff