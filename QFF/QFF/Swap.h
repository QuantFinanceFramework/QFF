#pragma once
#include "IInstrument.h"
#include "SwapLeg.h"
#include "BasicTradeInfo.h"

class Swap :
	public IInstrument
{
public:
	Swap() = delete;
	Swap(BasicTradeInfo info, SwapLeg receiveLeg, SwapLeg payLeg);
	~Swap() = default;
	double evaluate(const MarketData& marketData, const ICurrency& currency) const;

private:
	BasicTradeInfo m_info;
	SwapLeg m_receiveLeg;
	SwapLeg m_payLeg;
};

