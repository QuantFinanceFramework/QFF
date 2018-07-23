#include "Swap.h"
using std::move;

Swap::Swap(CashFlowCollection receiveLeg, CashFlowCollection payLeg):
	m_receiveLeg(move(receiveLeg)), m_payLeg(move(payLeg)){}

double Swap::evaluate(const IMarketData & marketData, const ICurrency & currency) const
{
	return m_receiveLeg.evaluate(marketData, currency) - m_payLeg.evaluate(marketData, currency);
}
