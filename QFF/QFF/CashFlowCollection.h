#pragma once
#include "MarketData.h"
#include "ICurrency.h"
#include "ICashFlow.h"
#include <vector>
#include <memory>

using std::vector;
using std::unique_ptr;

class CashFlowCollection
{
public:
	CashFlowCollection() = delete;
	CashFlowCollection(vector<unique_ptr<ICashFlow>> collection);

	CashFlowCollection(CashFlowCollection&&) = default;
	CashFlowCollection& operator=(CashFlowCollection&&) = default;

	virtual ~CashFlowCollection() = default;
	
	double evaluate(const IMarketData & marketData, const ICurrency& currency) const;

private:
	vector<unique_ptr<ICashFlow>> m_collection;

};

