#include "SwapScheduler.h"
#include <algorithm>
#include <vector>
#include "FixedCoupon.h"
#include "FloatingCoupon.h"
#include "numeric"

namespace qff {

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

unique_ptr<Swap> SwapScheduler::MakeInterestRateSwap(
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
  auto fixed =
      MakeFixedLeg(currency_code, notional, settlement_date, maturity_date,
                   discount_curve_name, fixed_frequency, fixed_payment_calendar,
                   fixed_business_day_convention, fixed_payment_lag,
                   fixed_day_counter, strike, is_front_stub, stub_date);
  auto floating = MakeFloatingLeg(
      currency_code, notional, settlement_date, maturity_date,
      discount_curve_name, floating_frequency, floating_payment_calendar,
      floating_business_day_convention, floating_payment_lag,
      floating_day_counter, index, leverage, margin, is_front_stub, stub_date);
  if (is_payer)
    return std::make_unique<Swap>(std::move(*floating), std::move(*fixed));
  return std::make_unique<Swap>(std::move(*fixed), std::move(*floating));
}

unique_ptr<Leg> SwapScheduler::MakeFixedLeg(
    const string& currency_code, double notional, date settlement_date,
    date maturity_date, const string& discount_curve_name, Frequency frequency,
    const ICalendar& payment_calendar, const IBusinessDayConvention& convention,
    Period payment_lag, const IDayCounter& day_counter, double strike,
    bool is_front_stub, date stub_date) {
  auto schedule =
      MakeSchedule(settlement_date, maturity_date, frequency, payment_calendar,
                   convention, is_front_stub, stub_date);

  vector<unique_ptr<ICashflow>> cf_collection;

  std::transform(schedule.begin(), std::prev(schedule.end()),
                 std::next(schedule.begin()), std::back_inserter(cf_collection),
                 [&](auto start, auto end) {
                   return std::make_unique<FixedCoupon>(
                       notional, currency_code, start, end,
                       ShiftDate(end, payment_lag, payment_calendar),
                       discount_curve_name, day_counter, strike);
                 });

  return std::make_unique<Leg>(std::move(cf_collection));
}
unique_ptr<Leg> SwapScheduler::MakeFloatingLeg(
    const string& currency_code, double notional, date settlement_date,
    date maturity_date, const string& discount_curve_name, Frequency frequency,
    const ICalendar& payment_calendar, const IBusinessDayConvention& convention,
    Period payment_lag, const IDayCounter& day_counter, const IIndex& index,
    double leverage, double margin, bool is_front_stub, date stub_date) {
  auto schedule =
      MakeSchedule(settlement_date, maturity_date, frequency, payment_calendar,
                   convention, is_front_stub, stub_date);

  vector<unique_ptr<ICashflow>> cf_collection;

  std::transform(
      schedule.begin(), std::prev(schedule.end()), std::next(schedule.begin()),
      std::back_inserter(cf_collection), [&](auto start, auto end) {
        return std::make_unique<FloatingCoupon>(
            notional, currency_code, start, end,
            ShiftDate(end, payment_lag, payment_calendar), discount_curve_name,
            day_counter, index, leverage, margin);
      });

  return std::make_unique<Leg>(std::move(cf_collection));
}
vector<date> SwapScheduler::MakeSchedule(
    date settlement_date, date maturity_date, Frequency frequency,
    const ICalendar& calendar, const IBusinessDayConvention& convention,
    bool is_front_stub, date stub_date) {
  auto schedule =
      MakeUnadjustedSchedule(settlement_date, maturity_date, frequency,
                             calendar, is_front_stub, stub_date);
  for (auto& element : schedule) {
    element = convention.Adjust(element, calendar);
  }
  return schedule;
}

vector<date> SwapScheduler::MakeUnadjustedSchedule(
    date settlement_date, date maturity_date, Frequency frequency,
    const ICalendar& calendar, bool is_front_stub, date stub_date) {
  const auto tenor = FrequencyToPeriod(frequency);
  vector<date> schedule;
  schedule.emplace_back(settlement_date);
  if (is_front_stub) {
    if (stub_date != settlement_date) schedule.emplace_back(stub_date);
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
}  // namespace qff
