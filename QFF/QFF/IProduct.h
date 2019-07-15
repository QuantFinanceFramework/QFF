#pragma once
#include "IMarketData.h"
#include "Currency.h"
#include <string>

using std::string;

class IInstrument
{
public:
	IInstrument() = default;
	virtual ~IInstrument() = default;

	virtual Currency evaluate(const IMarketData& marketData, const string& currencyCode) const = 0 ;
};

