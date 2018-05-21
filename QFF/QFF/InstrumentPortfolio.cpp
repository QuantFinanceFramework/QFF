#include "InstrumentPortfolio.h"
#include <numeric>
using std::accumulate;

InstrumentPortfolio::InstrumentPortfolio(vector<IInstrument*> portfolio) : m_portfolio{portfolio}{}

double InstrumentPortfolio::evaluate(MarketData marketData, const ICurrency & currency) const
{
	return accumulate(m_portfolio.begin(), m_portfolio.end(), 0.0, [&](double result, IInstrument* p) {return result + p->evaluate(marketData, currency); });
}
