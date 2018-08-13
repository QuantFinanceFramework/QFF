#include "MarketData.h"

double MarketData::getDiscountFactor(string curveName, date date) const
{
	return 0.0;
}

double MarketData::getForwardRateProjection(string curveName, date date) const
{
	return 0.0;
}

double MarketData::getSpot(string underlying) const
{
	return 0.0;
}

double MarketData::getForward(string underlying, date date) const
{
	return 0.0;
}

double MarketData::getVolatility(string underlying, date date, double strike) const
{
	return 0.0;
}
