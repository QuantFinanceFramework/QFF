#pragma once
#include "IMarketData.h"

class ICashflow
{
public:
	ICashflow() = default;
	virtual ~ICashflow() = default;

	virtual date getPaymentDate() const = 0;
	virtual double getPaymentAmount(const IMarketData& marketData) const = 0;
};

