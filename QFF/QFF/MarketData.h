#pragma once
#include "IMarketData.h"
#include "DiscountCurve.h"
#include <map>

using std::map;

class MarketData :
	public IMarketData
{
public:
	MarketData() = default;
	~MarketData() = default;
	double getDiscountFactor(string curveName, date date) const override;
	double getForwardRateProjection(string curveName, date date) const override;
	double getSpot(string underlying) const override;
	double getForward(string underlying, date date) const override;
	double getVolatility(string underlying, date date, double strike) const override;

private:
	date m_referenceDate;
	map<string, DiscountCurve> m_discountCurves;
};


