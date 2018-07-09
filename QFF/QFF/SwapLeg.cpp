#include "SwapLeg.h"
#include <numeric>
using std::accumulate;

double SwapLeg::evaluate(const MarketData & marketData, const ICurrency & currency) const
{
	return accumulate(m_leg.begin(), m_leg.end(), 0.0, [&](double result, unique_ptr<ICashFlow> p) {return result + p->evaluate(marketData, currency); });
}
