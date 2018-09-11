#pragma once
#include "IMarketData.h"
#include "EuroOptionInfo.h"
#include "ICurrency.h"

class IEuropeanOptionPricer
{
public:
	IEuropeanOptionPricer() = default;
	virtual ~IEuropeanOptionPricer() = default;
	virtual double evaluate(const IMarketData& marketData, const EuroOptionInfo& euroOptionInfo, string optionType, const ICurrency& currency) const = 0;
};
