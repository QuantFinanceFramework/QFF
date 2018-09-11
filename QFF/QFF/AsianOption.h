#pragma once
#include "IInstrument.h"
#include "IAsianOptionPricer.h"
#include "AsianOptionInfo.h"
#include <memory>

using std::shared_ptr;

class AsianOption :
	public IInstrument
{
public:
	AsianOption(AsianOptionInfo info, shared_ptr<IAsianOptionPricer> pricer);
	virtual ~AsianOption() = default;

	double evaluate(const IMarketData & marketData, const ICurrency& currency) const override;
	void setPricer(shared_ptr<IAsianOptionPricer> pricer);

private:
	AsianOptionInfo m_info;
	shared_ptr<IAsianOptionPricer> m_pricer;

};

