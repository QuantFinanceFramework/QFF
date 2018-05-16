#include "AsianOption.h"

AsianOption::AsianOption(BasicTradeInfo info, const IAsianOptionPricer& pricer) :m_info(info), m_pricer(&pricer) {}

double AsianOption::evaluate(MarketData marketData, const ICurrency& currency) const
{
	return m_pricer->evaluate(marketData, m_info, currency);
}

void AsianOption::setPricer(const IAsianOptionPricer & pricer)
{
	m_pricer = &pricer;
}
