#pragma once
#include <string>
#include <boost/date_time/gregorian/gregorian.hpp>

using std::string;
using boost::gregorian::date;

class IMarketData
{
public:
	IMarketData() = delete;
	virtual ~IMarketData() = default;
	virtual double getDiscountFactor(string curveName, date date) const = 0;
	virtual double getZeroRate(string curveName, date date) const = 0;
	virtual double getVolatility(string underlying, date date, double strike) const = 0;
	virtual double getSpot(string underlying) const = 0;
	virtual double getForward(string underlying, date date) const = 0;
	virtual double getDividendYieldEstimate(string underlying, date date) const = 0;
};



