#pragma once
#include "IMarketData.h"
#include "DiscountCurve.h"
#include <map>

using std::map;

class MarketData :
	public IMarketData
{
public:
	MarketData() = delete;
	~MarketData() = default;
	double getDiscountFactor(string curveName, date date) const override;

// Those are temporary variables to make those Options working
	// TODO: Remove those variables and replace them by the curves and getXXX methods
	double price;
	double volatility;
	double rate;
	double dividend;

private:
	date m_referenceDate;
	map<string, DiscountCurve> m_discountCurves;
};


