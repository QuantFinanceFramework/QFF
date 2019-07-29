#pragma once
#include <boost/date_time/gregorian/gregorian.hpp>
#include <memory>

namespace qff {
using boost::gregorian::date;
using std::unique_ptr;

class IDayCounter {
 public:
  IDayCounter() = default;
  virtual ~IDayCounter() = default;

  virtual unique_ptr<IDayCounter> Clone() const = 0;

  virtual double CalculateYearFraction(const date& start_date,
                                       const date& end_date, const bool& is_maturity = false) const = 0;
};
}  // namespace qff
