#pragma once
#include <boost/date_time/gregorian/gregorian.hpp>
#include <memory>

namespace qff_a {
class IDayCounter {
 public:
  virtual ~IDayCounter() = default;

  virtual std::unique_ptr<IDayCounter> Clone() const = 0;

  virtual double CalculateYearFraction(
      const boost::gregorian::date& start_date,
      const boost::gregorian::date& end_date,
      const bool& is_maturity = false) const = 0;
};
}  // namespace qff_a
