#pragma once
#include "IInstrument.h"
#include "IEuropeanOptionPricer.h"
#include "BasicTradeInfo.h"

class EuropeanOption :
	public IInstrument
{
public:
	EuropeanOption(BasicTradeInfo info, const IEuropeanOptionPricer& pricer);
	virtual ~EuropeanOption() = default;

	double evaluate() const override;
	void setPricer(const IEuropeanOptionPricer& pricer);

private:
	BasicTradeInfo m_info;
	const IEuropeanOptionPricer* m_pricer;

};

