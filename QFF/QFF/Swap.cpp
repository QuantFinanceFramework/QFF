#include "Swap.h"

Swap::Swap(CashFlowCollection receiveLeg, CashFlowCollection payLeg):
	m_receiveLeg(std::move(receiveLeg)), m_payLeg(std::move(payLeg)){}

double Swap::evaluate(const MarketData& marketData, const ICurrency & currency) const
{
	return m_receiveLeg.evaluate(marketData, currency) - m_payLeg.evaluate(marketData, currency);
}
