#pragma once
#include "IInstrument.h"
#include "CashFlowCollection.h"

class Swap :
	public IInstrument
{
public:
	Swap() = delete;
	Swap(CashFlowCollection receiveLeg, CashFlowCollection payLeg);
	~Swap() = default;
	double evaluate(const IMarketData & marketData, const ICurrency& currency) const;

private:
	CashFlowCollection m_receiveLeg;
	CashFlowCollection m_payLeg;
};

