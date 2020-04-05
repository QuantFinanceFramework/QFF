#include "SwapScheduler.h"

#include <algorithm>
#include <vector>

#include "CdsPremium.h"
#include "DateFunctions.h"
#include "FixedCoupon.h"
#include "FloatingCoupon.h"
#include "ProtectionLeg.h"
#include "numeric"

using boost::gregorian::date;
using std::string;
using std::unique_ptr;
using std::vector;

namespace qff_a {

using std::vector;

Period FrequencyToPeriod(Frequency frequency) {
  switch (frequency) {
    case Frequency::Daily:
      return Period{1, TimeUnit::d};
    case Frequency::Weekly:
      return Period{1, TimeUnit::w};
    case Frequency::Fortnightly:
      return Period{2, TimeUnit::w};
    case Frequency::Monthly:
      return Period{1, TimeUnit::m};
    case Frequency::Bimonthly:
      return Period{2, TimeUnit::m};
    case Frequency::Quarterly:
      return Period{3, TimeUnit::m};
    case Frequency::Semiannually:
      return Period{6, TimeUnit::m};
    case Frequency::Annually:
      return Period{1, TimeUnit::y};
    default:
      throw std::invalid_argument("invalid Frequency");
  }
}

std::unique_ptr<GenericSwap> SwapScheduler::MakeCreditDefaultSwap(
    const std::string& currency_code, double notional, date effective_date,
    date maturity_date, bool is_protection_buyer,
    const std::string& discount_curve_name,
    const std::string& survival_curve_name, Frequency premium_frequency,
    const ICalendar& premium_leg_calendar,
    const IBusinessDayConvention& premium_leg_convention,
    Period premium_payment_lag, const IDayCounter& premium_day_counter,
    double cds_spread, double recovery_rate, bool is_front_stub,
    date stub_date) {
  auto premium_leg = MakePremiumLeg(
      currency_code, notional, effective_date, maturity_date,
      discount_curve_name, survival_curve_name, premium_frequency,
      premium_leg_calendar, premium_leg_convention, premium_payment_lag,
      premium_day_counter, cds_spread, is_front_stub, stub_date);

  auto protection_leg = std::make_unique<ProtectionLeg>(
      notional, currency_code, effective_date, maturity_date,
      discount_curve_name, survival_curve_name, recovery_rate,
      Frequency::Daily);

  if (is_protection_buyer)
    return std::make_unique<GenericSwap>(std::move(protection_leg),
                                         std::move(premium_leg));
  return std::make_unique<GenericSwap>(std::move(premium_leg),
                                       std::move(protection_leg));
}

unique_ptr<InterestRateSwap> SwapScheduler::MakeInterestRateSwap(
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
    date stub_date, double stub_rate) {
  auto leg_notional = notional;

  if (is_payer) {
    leg_notional = -notional;
  }

  auto fixed =
      MakeFixedLeg(currency_code, leg_notional, settlement_date, maturity_date,
                   discount_curve_name, fixed_frequency, fixed_payment_calendar,
                   fixed_business_day_convention, fixed_payment_lag,
                   fixed_day_counter, strike, is_front_stub, stub_date);
  auto floating = MakeFloatingLeg(
      currency_code, leg_notional, settlement_date, maturity_date,
      discount_curve_name, floating_frequency, floating_payment_calendar,
      floating_business_day_convention, floating_payment_lag,
      floating_day_counter, index, leverage, margin, is_front_stub, stub_date);

  return std::make_unique<InterestRateSwap>(std::move(fixed),
                                            std::move(floating));
}

unique_ptr<BasisSwap> SwapScheduler::MakeBasisSwap(
    const std::string& currency_code, double notional, date settlement_date,
    date maturity_date, const std::string& discount_curve_name,
    Frequency m_leg_frequency, const ICalendar& m_leg_payment_calendar,
    const IBusinessDayConvention& m_leg_business_day_convention,
    Period m_leg_payment_lag, const IDayCounter& m_leg_day_counter,
    const IIndex& m_leg_index, double m_leg_leverage, double margin,
    bool m_leg_is_front_stub, date m_leg_stub_date, double m_leg_stub_rate,
    Frequency f_leg_frequency, const ICalendar& f_leg_payment_calendar,
    const IBusinessDayConvention& f_leg_business_day_convention,
    Period f_leg_payment_lag, const IDayCounter& f_leg_day_counter,
    const IIndex& f_leg_index, double f_leg_leverage, bool f_leg_is_front_stub,
    date f_leg_stub_date, double f_leg_stub_rate, bool is_paying_margin) {
  auto leg_notional = notional;

  if (is_paying_margin) {
    leg_notional = -notional;
  }

  auto margin_leg = MakeFloatingLeg(
      currency_code, leg_notional, settlement_date, maturity_date,
      discount_curve_name, m_leg_frequency, m_leg_payment_calendar,
      m_leg_business_day_convention, m_leg_payment_lag, m_leg_day_counter,
      m_leg_index, m_leg_leverage, margin, m_leg_is_front_stub,
      m_leg_stub_date);

  auto floating_leg = MakeFloatingLeg(
      currency_code, leg_notional, settlement_date, maturity_date,
      discount_curve_name, f_leg_frequency, f_leg_payment_calendar,
      f_leg_business_day_convention, f_leg_payment_lag, f_leg_day_counter,
      f_leg_index, f_leg_leverage, 0.0, f_leg_is_front_stub, f_leg_stub_date);

  return std::make_unique<BasisSwap>(std::move(margin_leg),
                                     std::move(floating_leg));
}

std::unique_ptr<GenericLeg> SwapScheduler::MakePremiumLeg(
    const std::string& currency_code, double notional, date start_date,
    date maturity_date, const std::string& discount_curve_name,
    const std::string& survival_curve_name, Frequency frequency,
    const ICalendar& payment_calendar, const IBusinessDayConvention& convention,
    Period payment_lag, const IDayCounter& day_counter, double cds_spread,
    bool is_front_stub, date stub_date) {
  auto schedule =
      MakeSchedule(start_date, maturity_date, frequency, payment_calendar,
                   convention, is_front_stub, stub_date);

  vector<unique_ptr<ICashflow>> cf_collection;

  std::transform(
      schedule.begin(), std::prev(schedule.end()), std::next(schedule.begin()),
      std::back_inserter(cf_collection), [&](auto start, auto end) {
        return std::make_unique<CdsPremium>(
            notional, currency_code, start, end,
            ShiftDate(end, payment_lag, payment_calendar), discount_curve_name,
            survival_curve_name, day_counter, cds_spread);
      });

  return std::make_unique<GenericLeg>(std::move(cf_collection));
}

unique_ptr<FixedLeg> SwapScheduler::MakeFixedLeg(
    const string& currency_code, double notional, date settlement_date,
    date maturity_date, const string& discount_curve_name, Frequency frequency,
    const ICalendar& payment_calendar, const IBusinessDayConvention& convention,
    Period payment_lag, const IDayCounter& day_counter, double strike,
    bool is_front_stub, date stub_date) {
  auto schedule =
      MakeSchedule(settlement_date, maturity_date, frequency, payment_calendar,
                   convention, is_front_stub, stub_date);

  vector<unique_ptr<FixedCoupon>> cf_collection;

  std::transform(schedule.begin(), std::prev(schedule.end()),
                 std::next(schedule.begin()), std::back_inserter(cf_collection),
                 [&](auto start, auto end) {
                   return std::make_unique<FixedCoupon>(
                       notional, currency_code, start, end,
                       ShiftDate(end, payment_lag, payment_calendar),
                       discount_curve_name, day_counter, strike);
                 });

  return std::make_unique<FixedLeg>(currency_code, std::move(cf_collection));
}
unique_ptr<FloatingLeg> SwapScheduler::MakeFloatingLeg(
    const string& currency_code, double notional, date settlement_date,
    date maturity_date, const string& discount_curve_name, Frequency frequency,
    const ICalendar& payment_calendar, const IBusinessDayConvention& convention,
    Period payment_lag, const IDayCounter& day_counter, const IIndex& index,
    double leverage, double margin, bool is_front_stub, date stub_date) {
  auto schedule =
      MakeSchedule(settlement_date, maturity_date, frequency, payment_calendar,
                   convention, is_front_stub, stub_date);

  vector<unique_ptr<FloatingCoupon>> cf_collection;

  std::transform(
      schedule.begin(), std::prev(schedule.end()), std::next(schedule.begin()),
      std::back_inserter(cf_collection), [&](auto start, auto end) {
        return std::make_unique<FloatingCoupon>(
            notional, currency_code, start, end,
            ShiftDate(end, payment_lag, payment_calendar), discount_curve_name,
            day_counter, index, leverage, margin);
      });

  return std::make_unique<FloatingLeg>(currency_code, std::move(cf_collection));
}
vector<date> SwapScheduler::MakeSchedule(
    date start_date, date maturity_date, Frequency frequency,
    const ICalendar& calendar, const IBusinessDayConvention& convention,
    bool is_front_stub, date stub_date) {
  auto schedule = MakeUnadjustedSchedule(start_date, maturity_date, frequency,
                                         calendar, is_front_stub, stub_date);
  std::transform(std::next(schedule.begin()), schedule.end(),
                 std::next(schedule.begin()),
                 [&](auto date) { return convention.Adjust(date, calendar); });
  return schedule;
}

vector<date> SwapScheduler::MakeUnadjustedSchedule(
    date start_date, date maturity_date, Frequency frequency,
    const ICalendar& calendar, bool is_front_stub, date stub_date) {
  const auto tenor = FrequencyToPeriod(frequency);
  vector<date> schedule;
  schedule.emplace_back(start_date);
  if (is_front_stub) {
    if (stub_date != start_date) schedule.emplace_back(stub_date);
    while (schedule.back() < maturity_date) {
      schedule.emplace_back(ShiftDate(schedule.back(), tenor, calendar));
    }
  } else {
    while (schedule.back() < stub_date) {
      schedule.emplace_back(ShiftDate(schedule.back(), tenor, calendar));
      schedule.emplace_back(maturity_date);
    }
  }
  return schedule;
}
}  // namespace qff_a
