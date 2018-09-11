#pragma once
#include <string>
#include <boost\date_time\gregorian\gregorian.hpp>

using std::string;
using boost::gregorian::date;


struct AsianOptionInfo
{
	AsianOptionInfo() = delete;
	string tradeID;
	string underlying;
	double strike;
	date pricingStartDate;
	date pricingEndDate;
	date settlementDate;

};