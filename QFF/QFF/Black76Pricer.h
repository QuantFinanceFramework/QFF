#pragma once
#include "IEuropeanOptionPricer.h"
class Black76Pricer :
	public IEuropeanOptionPricer
{
public:
	Black76Pricer() = default;
	virtual ~Black76Pricer() = default;
	double evaluate(const MarketData& marketData, const BasicTradeInfo& basicTradeInfo, string optionType, const ICurrency& currency) const override;
};