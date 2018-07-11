#pragma once
#include "IMarketData.h"
#include "ICurrency.h"

class IInstrument
{
public:
	IInstrument() = default;
	virtual ~IInstrument() = default;

	virtual double evaluate(const IMarketData & marketData, const ICurrency& currency) const =0 ;
};

