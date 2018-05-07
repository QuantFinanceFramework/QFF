#pragma once
#include "IInstrument.h"
#include "IAsianOptionPricer.h"
#include "BasicTradeInfo.h"

class AsianOption :
	public IInstrument
{
public:
	AsianOption(BasicTradeInfo info, const IAsianOptionPricer& pricer);
	virtual ~AsianOption() = default;

	double evaluate(MarketData marketData, const ICurrency& currency) const override;
	void setPricer(const IAsianOptionPricer& pricer);

private:
	BasicTradeInfo m_info;
	const IAsianOptionPricer* m_pricer;

};

