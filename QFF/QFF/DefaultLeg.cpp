#include "DefaultLeg.h"
#include <numeric>
#include "BaseCalendar.h"
#include "DateFunctions.h"

using boost::gregorian::date;
using std::string;

namespace qff {
DefaultLeg::DefaultLeg(double notional, string currency_code, date start_date,
                       date end_date, string discount_curve_name,
                       string survival_curve_name, double recovery_rate,
                       Frequency estimation_frequency)
    : notional_(notional),
      currency_code_(std::move(currency_code)),
      start_date_(start_date),
      end_date_(end_date),
      discount_curve_name_(std::move(discount_curve_name)),
      survival_curve_name_(std::move(survival_curve_name)),
      recovery_rate_(recovery_rate),
      estimation_frequency_(estimation_frequency) {}

Currency DefaultLeg::Evaluate(const IMarketData& market_data,
                              const string& currency_code) const {
  if (estimation_schedule_.empty()) {
    estimation_schedule_ = SwapScheduler::MakeUnadjustedSchedule(
        start_date_, end_date_, estimation_frequency_, BaseCalendar(), true,
        start_date_);
  }
  const auto discounted_default_probability = std::transform_reduce(
      estimation_schedule_.begin(), std::prev(estimation_schedule_.end()),
      std::next(estimation_schedule_.begin()), 0.0, std::plus(),
      [&](auto start, auto end) {
        return (market_data.GetSurvivalProbability(survival_curve_name_,
                                                   start) -
                market_data.GetSurvivalProbability(survival_curve_name_, end)) *
               market_data.GetDiscountFactor(discount_curve_name_, end);
      });
  const auto loss_given_default = notional_ * (1.0 - recovery_rate_);

  return Currency(currency_code,
                  loss_given_default * discounted_default_probability);
}
}  // namespace qff
