#include "Actual365.h"
#include "CurveInterpolator.h"
#include "Interpolation.h"
#include "ZeroRateCurve.h"
#include "gtest/gtest.h"

using namespace qff_a;
using namespace aad;
using boost::gregorian::date;
using std::vector;

TEST(ZeroRateCurveTest, SetValues) {
  const date pricing_date{2020, 1, 31};

  auto interpolator = CurveInterpolator<a_double>{
      &ProductLinearInterpol<a_double>, &ProductLinearExtrapol<a_double>};
  const Actual365 day_counter{};

  vector ff_pillars{
      date(2020, 2, 3), date(2020, 2, 13), date(2020, 2, 20), date(2020, 3, 6),
      date(2020, 4, 8), date(2020, 5, 6),  date(2020, 6, 8),  date(2020, 7, 8),
      date(2020, 8, 6), date(2020, 11, 6), date(2021, 2, 8),  date(2021, 8, 4),
      date(2022, 2, 4), date(2023, 2, 6),  date(2024, 2, 5),  date(2025, 2, 4),
      date(2026, 2, 4), date(2027, 2, 4),  date(2028, 2, 4),  date(2029, 2, 5),
      date(2030, 2, 4), date(2032, 2, 4),  date(2035, 2, 5),  date(2040, 2, 6),
      date(2045, 2, 6), date(2050, 2, 4),  date(2060, 2, 4)};

  vector ff_zeros{0.0157142629201847, 0.0160406863209875, 0.0160824439348794,
                  0.0161134455264112, 0.0160416235621084, 0.0159570512563784,
                  0.0158228733810686, 0.0156275866647933, 0.0154711858102748,
                  0.0148764481371773, 0.0142306690193869, 0.0132755841877428,
                  0.0126999728943875, 0.0121777751396347, 0.0120243963064879,
                  0.012061471498624,  0.0122453808443152, 0.0124577010089707,
                  0.0127362002510347, 0.0130122544457647, 0.0133075208792979,
                  0.0138503783924619, 0.0144669449582222, 0.0150971255186208,
                  0.0153189459232633, 0.0153272725963219, 0.0152905184676551};

  std::vector<a_double> ff_zeros_a(size(ff_zeros));
  convert_collection(ff_zeros.begin(), ff_zeros.end(), ff_zeros_a.begin());

  auto ff_curve = std::make_unique<ZeroRateCurve<a_double>>(
      pricing_date, "USD_FF", day_counter, interpolator, std::move(ff_pillars),
      ff_zeros_a);

  vector<double> zeros(ff_zeros.size());
  std::fill(zeros.begin(), zeros.end(), 0.0);
  ff_curve->SetValues(zeros);
  const auto result = ff_curve->GetDiscountFactor(date(2050, 2, 5)).value();
  EXPECT_NEAR(result, 1.0, 0.0000001);
}

TEST(ZeroRateCurveTest, SetPillars) {
  const date pricing_date{2020, 1, 31};

  auto interpolator = CurveInterpolator<a_double>{
      &ProductLinearInterpol<a_double>, &ProductLinearExtrapol<a_double>};
  const Actual365 day_counter{};

  vector ff_pillars{
      date(2020, 2, 3), date(2020, 2, 13), date(2020, 2, 20), date(2020, 3, 6),
      date(2020, 4, 8), date(2020, 5, 6),  date(2020, 6, 8),  date(2020, 7, 8),
      date(2020, 8, 6), date(2020, 11, 6), date(2021, 2, 8),  date(2021, 8, 4),
      date(2022, 2, 4), date(2023, 2, 6),  date(2024, 2, 5),  date(2025, 2, 4),
      date(2026, 2, 4), date(2027, 2, 4),  date(2028, 2, 4),  date(2029, 2, 5),
      date(2030, 2, 4), date(2032, 2, 4),  date(2035, 2, 5),  date(2040, 2, 6),
      date(2045, 2, 6), date(2050, 2, 4),  date(2060, 2, 4)};

  vector ff_zeros{0.0157142629201847, 0.0160406863209875, 0.0160824439348794,
                  0.0161134455264112, 0.0160416235621084, 0.0159570512563784,
                  0.0158228733810686, 0.0156275866647933, 0.0154711858102748,
                  0.0148764481371773, 0.0142306690193869, 0.0132755841877428,
                  0.0126999728943875, 0.0121777751396347, 0.0120243963064879,
                  0.012061471498624,  0.0122453808443152, 0.0124577010089707,
                  0.0127362002510347, 0.0130122544457647, 0.0133075208792979,
                  0.0138503783924619, 0.0144669449582222, 0.0150971255186208,
                  0.0153189459232633, 0.0153272725963219, 0.0152905184676551};

  std::vector<a_double> ff_zeros_a(size(ff_zeros));
  convert_collection(ff_zeros.begin(), ff_zeros.end(), ff_zeros_a.begin());

  auto ff_curve = std::make_unique<ZeroRateCurve<a_double>>(
      pricing_date, "USD_FF", day_counter, interpolator, std::move(ff_pillars),
      ff_zeros_a);

  vector pillars{date(2020, 2, 3), date(2030, 2, 3)};
  ff_curve->SetPillars(pillars);
  ff_curve->SetValues({0.0, 0.02});
  const auto result = ff_curve->GetDiscountFactor(date(2030, 2, 3)).value();
  EXPECT_NEAR(result, 0.818461626, 0.0000001);
}