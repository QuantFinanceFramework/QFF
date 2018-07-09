#include "SwapLeg.h"
#include <numeric>
using std::accumulate;

SwapLeg::SwapLeg(vector<ICashFlow*> leg) :m_leg{ leg } {};

double SwapLeg::evaluate(const MarketData & marketData, const ICurrency & currency) const
{
	return accumulate(m_leg.begin(), m_leg.end(), 0.0, [&](double result, ICashFlow* p) {return result + p->evaluate(marketData, currency); });
	return 0;
}
