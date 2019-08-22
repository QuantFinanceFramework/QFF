#pragma once
#include <boost/date_time/gregorian/gregorian.hpp>

namespace qff {

class IInterestRateCurve {
 public:
  IInterestRateCurve() = default;
  virtual ~IInterestRateCurve() = default;

  virtual double GetDiscountFactor(
      const boost::gregorian::date& query_date) const = 0;
  virtual double GetDiscountFactor(double query_time) const = 0;

  virtual double GetForwardRate(
      const boost::gregorian::date& start_date,
      const boost::gregorian::date& end_date) const = 0;
  virtual double GetForwardRate(double start_time, double end_time) const = 0;

  virtual double GetZeroRate(
      const boost::gregorian::date& query_date) const = 0;
  virtual double GetZeroRate(double query_time) const = 0;
};
}  // namespace qff
