#pragma once
#include "IProduct.h"
#include "Leg.h"

class Swap :
	public IProduct
{
public:
	Swap() = default;
	Swap(Leg&& receiveLeg, Leg&& payLeg);
	~Swap() = default;

	Currency evaluate(const IMarketData& marketData, const string& currencyCode) const override;

private:
	Leg receiveLeg_;
	Leg payLeg_;
};

