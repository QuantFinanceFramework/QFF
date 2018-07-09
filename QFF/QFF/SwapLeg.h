#pragma once
#include "MarketData.h"
#include "ICurrency.h"
#include "ICashFlow.h"
#include <vector>
#include <memory>
using std::vector;
using std::unique_ptr;

class SwapLeg
{
public:
	SwapLeg() = default;
	virtual ~SwapLeg() = default;
	double evaluate(const MarketData& marketData, const ICurrency& currency) const;

private:
	vector<unique_ptr<ICashFlow>> m_leg;

};

