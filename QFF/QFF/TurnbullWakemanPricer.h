#pragma once
#include "IAsianOptionPricer.h"
class TurnbullWakemanPricer :
	public IAsianOptionPricer
{
public:
	TurnbullWakemanPricer() = default;
	virtual ~TurnbullWakemanPricer() = default;
	double evaluate(const MarketData& marketData, const BasicTradeInfo& basicTradeInfo, const ICurrency& currency) const override;
};

