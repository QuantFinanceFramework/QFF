#include "ProductGenerator.h"

#include <stdexcept>
#include <vector>

#include "Actual360.h"
#include "AveragedOvernightIndex.h"
#include "CompositeCalendar.h"
#include "CompoundedOvernightIndex.h"
#include "IborIndex.h"
#include "LondonCalendar.h"
#include "ModifiedFollowing.h"
#include "NewYorkFedCalendar.h"
#include "ProtectionLeg.h"
#include "SwapMaker.h"
#include "Thirty360Isda.h"
#include "UsBondMarketCalendar.h"

using boost::gregorian::date;
using std::string;
using std::unique_ptr;
using std::vector;

namespace qff_a {
std::unique_ptr<IProduct> ProductGenerator::MakeProduct(
    std::string_view generator_name, double notional, date start_date,
    date maturity_date, double market_quote) {
  if (generator_name == "USSO") {
    return SwapMaker::MakeInterestRateSwap(
        "USD", notional, start_date, maturity_date, true, "USD_FF",
        Frequency::Annually, NewYorkFedCalendar(), ModifiedFollowing(),
        Period(2, TimeUnit::b), Actual360(), market_quote, Frequency::Annually,
        NewYorkFedCalendar(), ModifiedFollowing(), Period(2, TimeUnit::b),
        Actual360(),
        CompoundedOvernightIndex{"USD", "USD_FF", Actual360(),
                                 Period(0, TimeUnit::b), Period(1, TimeUnit::b),
                                 NewYorkFedCalendar(), ModifiedFollowing()},
        1, 0.0);
  }
  if (generator_name == "USOSFR") {
    return SwapMaker::MakeInterestRateSwap(
        "USD", notional, start_date, maturity_date, true, "USD_FF",
        Frequency::Annually, NewYorkFedCalendar(), ModifiedFollowing(),
        Period(2, TimeUnit::b), Actual360(), market_quote, Frequency::Annually,
        NewYorkFedCalendar(), ModifiedFollowing(), Period(2, TimeUnit::b),
        Actual360(),
        CompoundedOvernightIndex{"USD", "USD_SOFR", Actual360(),
                                 Period(0, TimeUnit::b), Period(1, TimeUnit::b),
                                 UsBondMarketCalendar(), ModifiedFollowing()},
        1, 0.0);
  }
  if (generator_name == "USSWAP") {
    return SwapMaker::MakeInterestRateSwap(
        "USD", notional, start_date, maturity_date, true, "USD_FF",
        Frequency::Semiannually,
        CompositeCalendar(NewYorkFedCalendar(), LondonCalendar()),
        ModifiedFollowing(), Period(0, TimeUnit::b), Thirty360Isda(),
        market_quote, Frequency::Quarterly,
        CompositeCalendar(NewYorkFedCalendar(), LondonCalendar()),
        ModifiedFollowing(), Period(0, TimeUnit::b), Actual360(),
        IborIndex{"USD", "USD_LIBOR_3M", Actual360(), Period(-2, TimeUnit::b),
                  LondonCalendar(), ModifiedFollowing(),
                  Period(3, TimeUnit::m)},
        1, 0.0);
  }
  if (generator_name == "USBG") {
    return SwapMaker::MakeBasisSwap(
        "USD", notional, start_date, maturity_date, true, "USD_FF",
        Frequency::Quarterly,
        CompositeCalendar(NewYorkFedCalendar(), LondonCalendar()),
        ModifiedFollowing(), Period(0, TimeUnit::b), Actual360(),
        AveragedOvernightIndex{"USD", "USD_FF", Actual360(),
                               Period(0, TimeUnit::b), Period(1, TimeUnit::b),
                               NewYorkFedCalendar(), ModifiedFollowing(),
                               Period(-2, TimeUnit::b), false},
        1.0, market_quote, Frequency::Quarterly,
        CompositeCalendar(NewYorkFedCalendar(), LondonCalendar()),
        ModifiedFollowing(), Period(0, TimeUnit::b), Actual360(),
        IborIndex{"USD", "USD_LIBOR_3M", Actual360(), Period(-2, TimeUnit::b),
                  LondonCalendar(), ModifiedFollowing(),
                  Period(3, TimeUnit::m)},
        1.0);
  }
  if (generator_name == "USSFVF") {
    return SwapMaker::MakeBasisSwap(
        "USD", notional, start_date, maturity_date, true, "USD_FF",
        Frequency::Quarterly, NewYorkFedCalendar(), ModifiedFollowing(),
        Period(2, TimeUnit::b), Actual360(),
        CompoundedOvernightIndex{"USD", "USD_SOFR", Actual360(),
                                 Period(0, TimeUnit::b), Period(1, TimeUnit::b),
                                 UsBondMarketCalendar(), ModifiedFollowing()},
        1.0, market_quote, Frequency::Quarterly, NewYorkFedCalendar(),
        ModifiedFollowing(), Period(2, TimeUnit::b), Actual360(),
        CompoundedOvernightIndex{"USD", "USD_FF", Actual360(),
                                 Period(0, TimeUnit::b), Period(1, TimeUnit::b),
                                 NewYorkFedCalendar(), ModifiedFollowing()},
        1.0);
  }
  if (generator_name == "USSRVL") {
    return SwapMaker::MakeBasisSwap(
        "USD", notional, start_date, maturity_date, true, "USD_FF",
        Frequency::Quarterly, NewYorkFedCalendar(), ModifiedFollowing(),
        Period(2, TimeUnit::b), Actual360(),
        CompoundedOvernightIndex{"USD", "USD_SOFR", Actual360(),
                                 Period(0, TimeUnit::b), Period(1, TimeUnit::b),
                                 UsBondMarketCalendar(), ModifiedFollowing()},
        1.0, market_quote, Frequency::Quarterly, NewYorkFedCalendar(),
        ModifiedFollowing(), Period(2, TimeUnit::b), Actual360(),
        IborIndex{"USD", "USD_LIBOR_3M", Actual360(), Period(-2, TimeUnit::b),
                  LondonCalendar(), ModifiedFollowing(),
                  Period(3, TimeUnit::m)},
        1.0);
  }
  throw std::invalid_argument("invalid generator name");
}
}  // namespace qff_a
