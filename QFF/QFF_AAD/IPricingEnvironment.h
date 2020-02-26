#pragma once
#include <boost/date_time/gregorian/gregorian.hpp>
#include <string>

namespace qff_a {
template <typename T>
class IPricingEnvironment {
 public:
  virtual ~IPricingEnvironment() = default;

  virtual boost::gregorian::date GetPricingDate() const = 0;

  virtual T GetDiscountFactor(
      const std::string& curve_name,
      const boost::gregorian::date& query_date) const = 0;

  virtual double GetPastRateFixing(
      const std::string& curve_name,
      const boost::gregorian::date& query_date) const = 0;
};
}  // namespace qff_a