#pragma once
#include <memory>
#include "IMarketData.h"
#include "boost/date_time/gregorian/gregorian.hpp"

namespace qff {

class IIndex {
 public:
  virtual ~IIndex() = default;

  virtual std::unique_ptr<IIndex> Clone() const = 0;

  virtual double GetRate(const boost::gregorian::date& accrual_start,
                         const boost::gregorian::date& accrual_end,
                         const IMarketData& market_data) const = 0;
};
}  // namespace qff