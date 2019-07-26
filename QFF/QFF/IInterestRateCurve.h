#pragma once
#include <boost/date_time/gregorian/gregorian.hpp>

namespace qff {
using boost::gregorian::date;

class IInterestRateCurve {
 public:
  IInterestRateCurve() = default;
  virtual ~IInterestRateCurve() = default;

  virtual double GetDiscountFactor(const date& query_date) const = 0;
  virtual double GetDiscountFactor(double query_time) const = 0;

  virtual double GetForwardRate(const date& start_date,
                                const date& end_date) const = 0;
  virtual double GetForwardRate(double start_time, double end_time) const = 0;

  virtual double GetZeroRate(const date& query_date) const = 0;
  virtual double GetZeroRate(double query_time) const = 0;
};
}  // namespace qff
