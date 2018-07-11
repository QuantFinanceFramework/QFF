#pragma once
#include "MarketData.h"
#include "ICurrency.h"
#include "ICashFlow.h"
#include <vector>

using std::vector;

class CashFlowCollection
{
public:
	CashFlowCollection() = delete;
	CashFlowCollection(vector<ICashFlow*> collection);
	virtual ~CashFlowCollection() = default;
	double evaluate(const MarketData& marketData, const ICurrency& currency) const;

private:
	vector<ICashFlow*> m_collection;

};

