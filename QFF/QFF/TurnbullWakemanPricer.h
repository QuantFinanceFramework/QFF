#pragma once
#include "IAsianOptionPricer.h"
class TurnbullWakemanPricer :
	public IAsianOptionPricer
{
public:
	TurnbullWakemanPricer() = default;
	virtual ~TurnbullWakemanPricer() = default;
	double evaluate(MarketData marketData, BasicTradeInfo basicTradeInfo, const ICurrency& currency) const override;
};

