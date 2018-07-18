#include "CashFlowCollection.h"
#include <numeric>
using std::accumulate;

CashFlowCollection::CashFlowCollection(vector<ICashFlow*> collection) :m_collection{ collection } {};

double CashFlowCollection::evaluate(const IMarketData & marketData, const ICurrency & currency) const
{
	return accumulate(m_collection.begin(), m_collection.end(), 0.0, [&](double result, ICashFlow* p) {return result + p->evaluate(marketData, currency); });
	return 0;
}
