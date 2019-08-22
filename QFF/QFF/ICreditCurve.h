#pragma once
#include <boost/date_time/gregorian/gregorian.hpp>

namespace qff {

class ICreditCurve {
 public:
  ICreditCurve() = default;
  virtual ~ICreditCurve() = default;

  virtual double GetSurvivalProbability(
      const boost::gregorian::date& query_date) const = 0;
  virtual double GetSurvivalProbability(double query_time) const = 0;
};
}  // namespace qff