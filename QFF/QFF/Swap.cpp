#include "Swap.h"

double Swap::evaluate(MarketData marketData, const ICurrency & currency) const
{
	return m_receiveLeg ->evaluate(marketData, currency) - m_payLeg->evaluate(marketData, currency);
}
