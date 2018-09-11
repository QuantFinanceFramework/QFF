#include "EuropeanOption.h"

EuropeanOption::EuropeanOption(EuroOptionInfo info, string optionType, shared_ptr<IEuropeanOptionPricer> pricer):m_info(info), m_optionType(optionType), m_pricer(pricer){}

double EuropeanOption::evaluate(const IMarketData & marketData, const ICurrency& currency) const
{
	return m_pricer->evaluate(marketData, m_info, m_optionType, currency);
}

void EuropeanOption::setPricer(shared_ptr<IEuropeanOptionPricer> pricer)
{
	m_pricer = pricer;
}
