#pragma once
#include <boost/date_time/gregorian/gregorian.hpp>
#include <string>

namespace qff {

class IMarketData {
 public:
  virtual ~IMarketData() = default;

  virtual boost::gregorian::date GetMarketDate() const = 0;

  virtual double GetDiscountFactor(
      const std::string& curve_name,
      const boost::gregorian::date& query_date) const = 0;

  virtual double GetSurvivalProbability(
      const std::string& curve_name,
      const boost::gregorian::date& query_date) const = 0;

  virtual double GetPastFixing(
      const std::string& curve_name,
      const boost::gregorian::date& query_date) const = 0;
};
}  // namespace qff
