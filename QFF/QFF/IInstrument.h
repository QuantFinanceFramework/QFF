#pragma once
#include "MarketData.h"
#include "ICurrency.h"

class IInstrument
{
public:
	IInstrument() = default;
	virtual ~IInstrument() = default;

	virtual double evaluate(const MarketData& marketData, const ICurrency& currency) const =0 ;
};

