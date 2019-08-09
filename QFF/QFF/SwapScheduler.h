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

  static unique_ptr<Swap> MakeBasisSwap(
      const string& currency_code, double notional, date settlement_date,
      date maturity_date, const string& discount_curve_name,
      Frequency r_leg_frequency, const ICalendar& r_leg_payment_calendar,
      const IBusinessDayConvention& r_leg_business_day_convention,
      Period r_leg_payment_lag, const IDayCounter& r_leg_day_counter,
      const IIndex& r_leg_index, double r_leg_leverage, double r_leg_margin,
      bool r_leg_is_front_stub, date r_leg_stub_date, double r_leg_stub_rate,
      Frequency p_leg_frequency, const ICalendar& p_leg_payment_calendar,
      const IBusinessDayConvention& p_leg_business_day_convention,
      Period p_leg_payment_lag, const IDayCounter& p_leg_day_counter,
      const IIndex& p_leg_index, double p_leg_leverage, double p_leg_margin,
      bool p_leg_is_front_stub, date p_leg_stub_date, double p_leg_stub_rate);

  static unique_ptr<Leg> MakeFixedLeg(
      const string& currency_code, double notional, date settlement_date,
      date maturity_date, const string& discount_curve_name,
      Frequency frequency, const ICalendar& payment_calendar,
      const IBusinessDayConvention& convention, Period payment_lag,
      const IDayCounter& day_counter, double strike, bool is_front_stub,
      date stub_date);

  static unique_ptr<Leg> MakeFloatingLeg(
      const string& currency_code, double notional, date settlement_date,
      date maturity_date, const string& discount_curve_name,
      Frequency frequency, const ICalendar& payment_calendar,
      const IBusinessDayConvention& convention, Period payment_lag,
      const IDayCounter& day_counter, const IIndex& index, double leverage,
      double margin, bool is_front_stub, date stub_date);

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
