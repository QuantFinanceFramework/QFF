#pragma once
#include <boost/date_time/gregorian/gregorian.hpp>
#include <vector>

namespace qff_a {
template <typename T>
class IInterestRateCurve {
 public:
  virtual ~IInterestRateCurve() = default;

  T GetDiscountFactor(const double time) const {
    return GetDiscountFactorImpl(time);
  }
  T GetDiscountFactor(const boost::gregorian::date& query_date) const {
    return GetDiscountFactorImpl(query_date);
  }

  std::vector<double> GetAdjoints() const { return GetAdjointsImpl(); }

 private:
  virtual T GetDiscountFactorImpl(double time) const = 0;
  virtual T GetDiscountFactorImpl(
      const boost::gregorian::date& query_date) const = 0;
  virtual std::vector<double> GetAdjointsImpl() const = 0;
};
}  // namespace qff_a