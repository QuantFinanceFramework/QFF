#include "Leg.h"
#include <numeric>
using std::accumulate;
using std::move;

Leg::Leg(vector<unique_ptr<ICashflow>> cashflows)
{
}

Currency Leg::evaluate(const IMarketData& marketData, const string& currencyCode) const
{
	return Currency();
}
