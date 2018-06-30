#include "Swap.h"

Swap::Swap(BasicTradeInfo info, unique_ptr<ISwapLeg> receiveLeg, unique_ptr<ISwapLeg> payLeg):
	m_info(info), m_receiveLeg(std::move(receiveLeg)), m_payLeg(std::move(payLeg)){}

double Swap::evaluate(MarketData marketData, const ICurrency & currency) const
{
	return m_receiveLeg ->evaluate(marketData, currency) - m_payLeg->evaluate(marketData, currency);
}
