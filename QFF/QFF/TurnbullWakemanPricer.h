#pragma once
#include "IAsianOptionPricer.h"
class TurnbullWakemanPricer :
	public IAsianOptionPricer
{
public:
	TurnbullWakemanPricer() = default;
	virtual ~TurnbullWakemanPricer() = default;
	double evaluate(const IMarketData& marketData, const AsianOptionInfo& asianOptionInfo, const ICurrency& currency) const override;
};

