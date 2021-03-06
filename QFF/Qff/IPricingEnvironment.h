#pragma once
#include <boost/date_time/gregorian/gregorian.hpp>

#include "IInterestRateCurve.h"

namespace qff_a {
template <typename T>
class IPricingEnvironment {
 public:
  virtual ~IPricingEnvironment() = default;

  virtual boost::gregorian::date GetPricingDate() const = 0;

  virtual T GetDiscountFactor(
      const std::string& curve_name,
      const boost::gregorian::date& query_date) const = 0;

  virtual T GetSurvivalProbability(
      const std::string& curve_name,
      const boost::gregorian::date& query_date) const = 0;

  // Currencies are quoted in relation to another currency,
  // i.e. base currency / quote currency.
  virtual T GetFxToday(std::string base_currency,
                       std::string quote_currency) const = 0;

  virtual double GetPastRateFixing(
      const std::string& curve_name,
      const boost::gregorian::date& query_date) const = 0;

  virtual void PutInterestRateCurvesOnTape() const = 0;

  virtual IrDeltas GetInterestRateAdjoints() const = 0;

  virtual IrDeltas GetInterestRateAdjoints(
      const std::string& curve_name) const = 0;

  virtual std::vector<double> GetCreditAdjoints(
      const std::string& curve_name) const = 0;
};
}  // namespace qff_a