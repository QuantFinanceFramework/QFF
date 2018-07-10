#pragma once
#include "MarketData.h"
#include "ICurrency.h"
#include "ICashFlow.h"
#include <vector>

using std::vector;

class SwapLeg
{
public:
	SwapLeg() = delete;
	SwapLeg(vector<ICashFlow*> leg);
	virtual ~SwapLeg() = default;
	double evaluate(const MarketData& marketData, const ICurrency& currency) const;

private:
	vector<ICashFlow*> m_leg;

};

