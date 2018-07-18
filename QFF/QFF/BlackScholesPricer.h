#pragma once
#include "IEuropeanOptionPricer.h"
class BlackScholesPricer :
	public IEuropeanOptionPricer
{
public:
	BlackScholesPricer() = default;
	virtual ~BlackScholesPricer() = default;
	double evaluate(const IMarketData& marketData, const BasicTradeInfo& basicTradeInfo, string optionType, const ICurrency& currency) const override;
};

