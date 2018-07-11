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
};



