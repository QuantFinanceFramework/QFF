#pragma once
#include <boost/date_time/gregorian/gregorian.hpp>
#include <vector>

namespace qff_a {
template <typename T>
class ICreditCurve {
 public:
  virtual ~ICreditCurve() = default;

  virtual T GetSurvivalProbability(
      const boost::gregorian::date& query_date) const = 0;

  virtual std::vector<double> GetAdjoints() const = 0;
};
}  // namespace qff_a