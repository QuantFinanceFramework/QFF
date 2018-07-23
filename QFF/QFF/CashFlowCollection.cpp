#include "CashFlowCollection.h"
#include <numeric>
using std::accumulate;
using std::move;

CashFlowCollection::CashFlowCollection(vector<unique_ptr<ICashFlow>> collection) :m_collection{ move(collection) } {};

double CashFlowCollection::evaluate(const IMarketData & marketData, const ICurrency & currency) const
{
	return accumulate(m_collection.begin(), m_collection.end(), 0.0, [&](double result, auto& p) {return result + p->evaluate(marketData, currency); });
}
