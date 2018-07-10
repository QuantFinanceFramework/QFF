#pragma once
#include "IInstrument.h"
#include <vector>
using std::vector;

class InstrumentPortfolio :
	public IInstrument
{
public:
	InstrumentPortfolio(vector<IInstrument*> portfolio);
	~InstrumentPortfolio() = default;

	double evaluate(const MarketData& marketData, const ICurrency& currency) const override;

private:
	vector<IInstrument*> m_portfolio;
};

