#pragma once
#include "IMarketData.h"
#include "AsianOptionInfo.h"
#include "ICurrency.h"

class IAsianOptionPricer
{
public:
	IAsianOptionPricer() = default;
	virtual ~IAsianOptionPricer() = default;
	virtual double evaluate(const IMarketData& marketData, const AsianOptionInfo& asianOptionInfo, const ICurrency& currency) const = 0;
};
