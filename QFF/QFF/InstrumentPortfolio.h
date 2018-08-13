#pragma once
#include "IInstrument.h"
#include <vector>
#include <memory>

using std::vector;
using std::shared_ptr;

class InstrumentPortfolio :
	public IInstrument
{
public:
	InstrumentPortfolio(vector<shared_ptr<IInstrument>> portfolio);
	~InstrumentPortfolio() = default;

	double evaluate(const IMarketData & marketData, const ICurrency& currency) const override;

private:
	vector<shared_ptr<IInstrument>> m_portfolio;
};

