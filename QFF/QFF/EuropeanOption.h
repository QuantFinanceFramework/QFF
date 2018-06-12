#pragma once
#include "IInstrument.h"
#include "IEuropeanOptionPricer.h"
#include "BasicTradeInfo.h"

class EuropeanOption :
	public IInstrument
{
public:
	EuropeanOption(BasicTradeInfo info, string optionType, const IEuropeanOptionPricer& pricer);
	virtual ~EuropeanOption() = default;

	double evaluate(MarketData marketData, const ICurrency& currency) const override;
	void setPricer(const IEuropeanOptionPricer& pricer);

private:
	BasicTradeInfo m_info;
	const IEuropeanOptionPricer* m_pricer;
	string m_optionType;

};

