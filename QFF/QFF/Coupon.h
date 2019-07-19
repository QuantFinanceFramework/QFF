#pragma once
#include <boost/date_time/gregorian/gregorian.hpp>
#include <memory>
#include <string>
#include "ICashflow.h"
#include "IDayCounter.h"

namespace qff {
using boost::gregorian::date;
using std::string;
using std::unique_ptr;

class Coupon : public ICashflow {
 public:
  Coupon() = default;
  Coupon(double notional, const string& currencyCode, date paymentDate,
         date accrualStartDate, date accrualEndDate,
         const IDayCounter& dayCounter);
  ~Coupon() = default;

  string getCurrency() const;
  date getPaymentDate() const final;

 protected:
  double calculateAccrualFactor() const;

  double notional_;
  string currencyCode_;
  date paymentDate_;
  date accrualStartDate_;
  date accrualEndDate_;
  unique_ptr<IDayCounter> dayCounter_;
};
}  // namespace qff
