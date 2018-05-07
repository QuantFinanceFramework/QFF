#pragma once
#include "IEuropeanOptionPricer.h"
class BlackScholesPricer :
	public IEuropeanOptionPricer
{
public:
	BlackScholesPricer() = default;
	virtual ~BlackScholesPricer() = default;
	double evaluate(MarketData marketData, const ICurrency& currency) const override;
};

