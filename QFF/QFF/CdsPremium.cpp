#include "CdsPremium.h"
namespace qff {
CdsPremium::CdsPremium(double notional, string currency_code,
                       date accrual_start_date, date accrual_end_date,
                       date payment_date, string discount_curve_name,
                       string survival_curve_name,
                       const IDayCounter& day_counter, double cds_spread)
    : notional_(notional),
      currency_code_(std::move(currency_code)),
      accrual_start_date_(accrual_start_date),
      accrual_end_date_(accrual_end_date),
      accrual_factor_(day_counter.CalculateYearFraction(accrual_start_date,
                                                        accrual_end_date)),
      payment_date_(payment_date),
      discount_curve_name_(std::move(discount_curve_name)),
      survival_curve_name_(std::move(survival_curve_name)),
      day_counter_(day_counter.Clone()),
      cds_spread_(cds_spread) {}

Currency CdsPremium::Evaluate(const IMarketData& market_data,
                              const string& currency_code) const {
  const auto discount_factor =
      market_data.GetDiscountFactor(discount_curve_name_, payment_date_);

  const auto survival_probability_start = market_data.GetSurvivalProbability(survival_curve_name_, accrual_start_date_);

  const auto survival_probability_end = market_data.GetSurvivalProbability(survival_curve_name_,accrual_end_date_);

  const auto npv = GetPaymentAmount(market_data) * discount_factor * 0.5 *
                   (survival_probability_end + survival_probability_start);

  return Currency(currency_code, npv);
}

date CdsPremium::GetPaymentDate() const { return payment_date_; }

double CdsPremium::GetPaymentAmount(const IMarketData& market_data) const {
  return notional_ * cds_spread_ * accrual_factor_;
}
}  // namespace qff
