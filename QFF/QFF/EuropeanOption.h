#pragma once
#include "IInstrument.h"
#include "IEuropeanOptionPricer.h"
#include "BasicTradeInfo.h"
#include <memory>

using std::shared_ptr;

class EuropeanOption :
	public IInstrument
{
public:
	EuropeanOption(BasicTradeInfo info, string optionType, shared_ptr<IEuropeanOptionPricer> pricer);
	virtual ~EuropeanOption() = default;

	double evaluate(const IMarketData & marketData, const ICurrency& currency) const override;
	void setPricer(shared_ptr<IEuropeanOptionPricer> pricer);

private:
	BasicTradeInfo m_info;
	shared_ptr<IEuropeanOptionPricer> m_pricer;
	string m_optionType;

};

