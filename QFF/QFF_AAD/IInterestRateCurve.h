#pragma once
#include <boost/date_time/gregorian/gregorian.hpp>
#include "IrDeltas.h"

namespace qff_a {
template <typename T>
class IInterestRateCurve {
 public:
  virtual ~IInterestRateCurve() = default;

  virtual T GetDiscountFactor(
      const boost::gregorian::date& query_date) const = 0;

  virtual void PutOnTape() const = 0;

  virtual IrDeltas GetAdjoints() const = 0;
};
}  // namespace qff_a