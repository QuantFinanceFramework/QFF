#include "EuropeanOption.h"

EuropeanOption::EuropeanOption(BasicTradeInfo info, const IEuropeanOptionPricer& pricer):m_info(info), m_pricer(&pricer){}

double EuropeanOption::evaluate(MarketData marketData, const ICurrency& currency) const
{
	return m_pricer->evaluate(marketData, currency);
}

void EuropeanOption::setPricer(const IEuropeanOptionPricer & pricer)
{
	m_pricer = &pricer;
}
