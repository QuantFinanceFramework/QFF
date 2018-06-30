#pragma once
#include "IInstrument.h"
#include "ISwapLeg.h"
#include "BasicTradeInfo.h"
#include <memory>

using std::unique_ptr;

class Swap :
	public IInstrument
{
public:
	Swap() = default;
	~Swap() = default;
	double evaluate(MarketData marketData, const ICurrency& currency) const override;

private:
	BasicTradeInfo m_info;
	unique_ptr<ISwapLeg> m_receiveLeg;
	unique_ptr<ISwapLeg> m_payLeg;
};

