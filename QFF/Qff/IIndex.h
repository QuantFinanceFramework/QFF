#pragma once
#include <memory>

#include "../AAD/aad_all.h"
#include "IPricingEnvironment.h"
#include "boost/date_time/gregorian/gregorian.hpp"

namespace qff_a {
class IIndex {
 public:
  virtual ~IIndex() = default;

  virtual std::unique_ptr<IIndex> Clone() const = 0;

  virtual double GetRate(
      const boost::gregorian::date& accrual_start,
      const boost::gregorian::date& accrual_end,
      const IPricingEnvironment<double>& pricing_environment) const = 0;

  virtual aad::a_double GetRate(
      const boost::gregorian::date& accrual_start,
      const boost::gregorian::date& accrual_end,
      const IPricingEnvironment<aad::a_double>& pricing_environment) const = 0;
};
}  // namespace qff_a