#pragma once
#include <boost/date_time/gregorian/gregorian.hpp>
#include <string>

namespace qff {
using boost::gregorian::date;
using std::string;

class IMarketData {
 public:
  IMarketData() = default;
  virtual ~IMarketData() = default;

  virtual date GetMarketDate() const = 0;

  virtual double GetDiscountFactor(const string& curve_name,
                                   const date& query_date) const = 0;

  virtual double GetSurvivalProbability(const string& curve_name,
                                   const date& query_date) const = 0;

  virtual double GetPastFixing(const string& curve_name,
                               const date& query_date) const = 0;
};
}  // namespace qff
