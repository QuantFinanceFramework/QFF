#pragma once
#include <memory>
#include <string>

#include "BasisSwap.h"
#include "FixedLeg.h"
#include "FloatingLeg.h"
#include "IBusinessDayConvention.h"
#include "ICalendar.h"
#include "IDayCounter.h"
#include "IIndex.h"
#include "InterestRateSwap.h"
#include "GenericLeg.h"
#include "Period.h"
#include "GenericSwap.h"
#include "boost/date_time/gregorian/gregorian.hpp"

namespace qff_a {

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
  static std::unique_ptr<GenericSwap> MakeCreditDefaultSwap(
      const std::string& currency_code, double notional,
      boost::gregorian::date effective_date,
      boost::gregorian::date maturity_date, bool is_protection_buyer,
      const std::string& discount_curve_name,
      const std::string& survival_curve_name, Frequency premium_frequency,
      const ICalendar& premium_leg_calendar,
      const IBusinessDayConvention& premium_leg_convention,
      Period premium_payment_lag, const IDayCounter& premium_day_counter,
      double cds_spread, double recovery_rate, bool is_front_stub,
      boost::gregorian::date stub_date);

  static std::unique_ptr<InterestRateSwap> MakeInterestRateSwap(
      const std::string& currency_code, double notional,
      boost::gregorian::date settlement_date,
      boost::gregorian::date maturity_date, bool is_payer,
      const std::string& discount_curve_name, Frequency fixed_frequency,
      const ICalendar& fixed_payment_calendar,
      const IBusinessDayConvention& fixed_business_day_convention,
      Period fixed_payment_lag, const IDayCounter& fixed_day_counter,
      double strike, Frequency floating_frequency,
      const ICalendar& floating_payment_calendar,
      const IBusinessDayConvention& floating_business_day_convention,
      Period floating_payment_lag, const IDayCounter& floating_day_counter,
      const IIndex& index, double leverage, double margin, bool is_front_stub,
      boost::gregorian::date stub_date, double stub_rate);

  static std::unique_ptr<BasisSwap> MakeBasisSwap(
      const std::string& currency_code, double notional,
      boost::gregorian::date settlement_date,
      boost::gregorian::date maturity_date,
      const std::string& discount_curve_name, Frequency m_leg_frequency,
      const ICalendar& m_leg_payment_calendar,
      const IBusinessDayConvention& m_leg_business_day_convention,
      Period m_leg_payment_lag, const IDayCounter& m_leg_day_counter,
      const IIndex& m_leg_index, double m_leg_leverage, double margin,
      bool m_leg_is_front_stub, boost::gregorian::date m_leg_stub_date,
      double m_leg_stub_rate, Frequency f_leg_frequency,
      const ICalendar& f_leg_payment_calendar,
      const IBusinessDayConvention& f_leg_business_day_convention,
      Period f_leg_payment_lag, const IDayCounter& f_leg_day_counter,
      const IIndex& f_leg_index, double f_leg_leverage,
      bool f_leg_is_front_stub, boost::gregorian::date f_leg_stub_date,
      double f_leg_stub_rate, bool is_paying_margin);

  static std::unique_ptr<GenericLeg> MakePremiumLeg(
      const std::string& currency_code, double notional,
      boost::gregorian::date start_date, boost::gregorian::date maturity_date,
      const std::string& discount_curve_name,
      const std::string& survival_curve_name, Frequency frequency,
      const ICalendar& payment_calendar,
      const IBusinessDayConvention& convention, Period payment_lag,
      const IDayCounter& day_counter, double cds_spread, bool is_front_stub,
      boost::gregorian::date stub_date);

  static std::unique_ptr<FixedLeg> MakeFixedLeg(
      const std::string& currency_code, double notional,
      boost::gregorian::date settlement_date,
      boost::gregorian::date maturity_date,
      const std::string& discount_curve_name, Frequency frequency,
      const ICalendar& payment_calendar,
      const IBusinessDayConvention& convention, Period payment_lag,
      const IDayCounter& day_counter, double strike, bool is_front_stub,
      boost::gregorian::date stub_date);

  static std::unique_ptr<FloatingLeg> MakeFloatingLeg(
      const std::string& currency_code, double notional,
      boost::gregorian::date settlement_date,
      boost::gregorian::date maturity_date,
      const std::string& discount_curve_name, Frequency frequency,
      const ICalendar& payment_calendar,
      const IBusinessDayConvention& convention, Period payment_lag,
      const IDayCounter& day_counter, const IIndex& index, double leverage,
      double margin, bool is_front_stub, boost::gregorian::date stub_date);

  static std::vector<boost::gregorian::date> MakeSchedule(
      boost::gregorian::date start_date, boost::gregorian::date maturity_date,
      Frequency frequency, const ICalendar& calendar,
      const IBusinessDayConvention& convention, bool is_front_stub,
      boost::gregorian::date stub_date);

  static std::vector<boost::gregorian::date> MakeUnadjustedSchedule(
      boost::gregorian::date start_date, boost::gregorian::date maturity_date,
      Frequency frequency, const ICalendar& calendar, bool is_front_stub,
      boost::gregorian::date stub_date);
};
}  // namespace qff_a
