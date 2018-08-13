#include "AsianOption.h"

AsianOption::AsianOption(BasicTradeInfo info, shared_ptr<IAsianOptionPricer> pricer) :m_info(info), m_pricer(pricer) {}

double AsianOption::evaluate(const IMarketData & marketData, const ICurrency& currency) const
{
	return m_pricer->evaluate(marketData, m_info, currency);
}

void AsianOption::setPricer(shared_ptr<IAsianOptionPricer> pricer)
{
	m_pricer = pricer;
}
