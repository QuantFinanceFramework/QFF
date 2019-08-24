#include <Actual360.h>
#include <Actual365.h>
#include <CurveInterpolator.h>
#include <DiscountFactorCurve.h>
#include <Following.h>
#include <Interpolation.h>
#include <MarketData.h>
#include <NewYorkCalendar.h>
#include <SurvivalCurve.h>
#include <SwapScheduler.h>
#include <memory>
#include <vector>

using namespace qff;
using boost::gregorian::date;
using std::map;
using std::string;
using std::unique_ptr;
using std::vector;

int main() {
  const date market_date{2019, 5, 31};

  const CurveInterpolator interpolator{LogLinearInterpol, LogLinearExtrapol};
  const Actual365 day_counter{};

  vector ff_pillars{date(2019, 5, 31), date(2019, 6, 3),  date(2019, 6, 13),
                    date(2019, 6, 20), date(2019, 7, 9),  date(2019, 8, 7),
                    date(2019, 9, 6),  date(2019, 10, 8), date(2019, 11, 6),
                    date(2019, 12, 6), date(2020, 3, 6),  date(2020, 6, 8),
                    date(2020, 12, 4), date(2021, 6, 4),  date(2022, 6, 6),
                    date(2023, 6, 5),  date(2024, 6, 4),  date(2025, 6, 4),
                    date(2026, 6, 4),  date(2027, 6, 4),  date(2028, 6, 5),
                    date(2029, 6, 4),  date(2031, 6, 4),  date(2034, 6, 5),
                    date(2039, 6, 6),  date(2044, 6, 6),  date(2049, 6, 4),
                    date(2059, 6, 4)};

  vector ff_dfs{1.0,
                0.999800872992796,
                0.999134993986712,
                0.998669446518402,
                0.997428414040305,
                0.995540161499476,
                0.993634144205857,
                0.991654907092137,
                0.989938162494432,
                0.988214977654795,
                0.983430093567905,
                0.978835965540289,
                0.971198658276277,
                0.963841590707898,
                0.948631397518242,
                0.932724044489571,
                0.916266041183543,
                0.899136394875739,
                0.881530083338169,
                0.863601830811111,
                0.845226273120938,
                0.826782193884814,
                0.790049832392724,
                0.737810161210047,
                0.659506357869887,
                0.592244424624496,
                0.532421621864522,
                0.432473480293818};

  auto fed_funds = std::make_unique<DiscountFactorCurve>(
      market_date, std::move(ff_pillars), ff_dfs, interpolator, day_counter);

  map<string, unique_ptr<IInterestRateCurve>> curve_set;
  curve_set.emplace(std::make_pair("USD_FedFunds", std::move(fed_funds)));

  vector jpm_pillars{date(2019, 5, 31), date(2019, 12, 20), date(2020, 6, 22),
                     date(2021, 6, 21), date(2022, 6, 20),  date(2023, 6, 20),
                     date(2024, 6, 20), date(2026, 6, 22),  date(2029, 6, 20)};
  vector jpm_sps{1.0,
                 0.998242769265384,
                 0.996651615424404,
                 0.9910946001613,
                 0.983018988614917,
                 0.971788154053126,
                 0.956725511564442,
                 0.915853317711067,
                 0.856150071905017};

  auto jpm_credit = std::make_unique<SurvivalCurve>(
      market_date, std::move(jpm_pillars), jpm_sps, interpolator, day_counter);

  map<string, unique_ptr<ICreditCurve>> credit_curve_set;
  credit_curve_set.emplace(std::make_pair("JPM", std::move(jpm_credit)));

  map<string, map<date, double>> past_fixing_set;

  const MarketData market{market_date, std::move(curve_set),
                          std::move(credit_curve_set),
                          std::move(past_fixing_set)};

  auto jpm_cds = SwapScheduler::MakeCreditDefaultSwap(
      "USD", 1000000.0, date(2019, 6, 1), date(2029, 6, 20), true,
      "USD_FedFunds", "JPM", Frequency::Quarterly, NewYorkCalendar(),
      Following(), Period(0, TimeUnit::b), Actual360(), 0.00874761, 0.4, true,
      date(2019, 9, 20));

  std::cout.precision(15);

  std::cout << "JPM CDS NPV: " << jpm_cds->Evaluate(market, "USD").amount << '\n';
  return 0;
}
