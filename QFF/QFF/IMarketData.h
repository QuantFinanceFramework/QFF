#pragma once
#include <string>
#include <boost/date_time/gregorian/gregorian.hpp>

using std::string;
using boost::gregorian::date;

class IMarketData
{
public:
	IMarketData() = default;
	virtual ~IMarketData() = default;

	virtual double getDiscountFactor(string curveName, date queryDate) const = 0;
	virtual double getForwardRate(string curveName, date startDate, date endDate) const = 0;
	virtual double getZeroRate(string curveName, date queryDate) const = 0;
};



