#include "InstrumentPortfolio.h"
#include <numeric>
using std::accumulate;

InstrumentPortfolio::InstrumentPortfolio(vector<shared_ptr<IInstrument>> portfolio) : m_portfolio{portfolio}{}

double InstrumentPortfolio::evaluate(const IMarketData & marketData, const ICurrency & currency) const
{
	return accumulate(m_portfolio.begin(), m_portfolio.end(), 0.0, [&](double result, auto& p) {return result + p->evaluate(marketData, currency); });
}
