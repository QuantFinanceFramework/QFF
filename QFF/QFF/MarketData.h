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

private:
	date m_referenceDate;
	map<string, DiscountCurve> m_discountCurves;
};


