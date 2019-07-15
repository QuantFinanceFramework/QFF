#pragma once
#include "IMarketData.h"
#include "Currency.h"
#include <string>

using std::string;

class IProduct
{
public:
	IProduct() = default;
	virtual ~IProduct() = default;

	virtual Currency evaluate(const IMarketData& marketData, const string& currencyCode) const = 0;
};

