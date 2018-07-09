#pragma once
#include "IInstrument.h"
#include "SwapLeg.h"
#include "BasicTradeInfo.h"

class Swap :
	public IInstrument
{
public:
	Swap() = delete;
	Swap(SwapLeg receiveLeg, SwapLeg payLeg);
	~Swap() = default;
	double evaluate(const MarketData& marketData, const ICurrency& currency) const;

private:
	SwapLeg m_receiveLeg;
	SwapLeg m_payLeg;
};

