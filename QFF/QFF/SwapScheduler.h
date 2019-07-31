#pragma once
#include <memory>
#include <string>
#include "IBusinessDayConvention.h"
#include "ICalendar.h"
#include "IDayCounter.h"
#include "IIndex.h"
#include "Leg.h"
#include "Period.h"
#include "Swap.h"
#include "boost/date_time/gregorian/gregorian.hpp"

namespace qff {
using boost::gregorian::date;
using std::string;
using std::unique_ptr;

enum class Frequency {
  Daily,
  Weekly,
  Fortnightly,
  Monthly,
  Quarterly,
  Semiannually,
  Annually
};

Period FrequencyToPeriod(Frequency frequency);

class SwapScheduler {
 public:
  static unique_ptr<Swap> MakeInterestRateSwap(
	  const string& currency_code, double notional, date settlement_date,
	  date maturity_date, bool is_payer, const string& discount_curve_name,
	  Frequency fixed_frequency, const ICalendar& fixed_payment_calendar,
	  const IBusinessDayConvention& fixed_business_day_convention,
	  Period fixed_payment_lag, const IDayCounter& fixed_day_counter,
	  double strike, Frequency floating_frequency,
	  const ICalendar& floating_payment_calendar,
	  const IBusinessDayConvention& floating_business_day_convention,
	  Period floating_payment_lag, const IDayCounter& floating_day_counter,
	  const IIndex& index, double leverage, double margin, bool is_front_stub,
	  date stub_date, double stub_rate);

  static unique_ptr<Leg> MakeFixedLeg(
	  const string& currency_code, double notional, date settlement_date,
	  date maturity_date, const string& discount_curve_name,
	  Frequency frequency, const ICalendar& payment_calendar,
	  const IBusinessDayConvention& convention,
	  Period payment_lag, const IDayCounter& day_counter,
	  double strike, bool is_front_stub, date stub_date);

  static unique_ptr<Leg> MakeFloatingLeg(
      const string& currency_code, double notional, date settlement_date,
      date maturity_date, const string& discount_curve_name,
      Frequency frequency, const ICalendar& payment_calendar,
      const IBusinessDayConvention& convention,
      Period payment_lag, const IDayCounter& day_counter,
      const IIndex& index, double leverage, double margin, bool is_front_stub,
      date stub_date);

  static vector<date> MakeSchedule(date settlement_date, date maturity_date,
                                   Frequency frequency,
                                   const ICalendar& calendar,
                                   const IBusinessDayConvention& convention,
                                   bool is_front_stub, date stub_date);

  static vector<date> MakeUnadjustedSchedule(
      date settlement_date, date maturity_date, Frequency frequency,
      const ICalendar& calendar, bool is_front_stub, date stub_date);
};
}  // namespace qff
