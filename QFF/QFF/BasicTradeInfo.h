#pragma once
#include <string>
#include <boost\date_time\gregorian\gregorian.hpp>
using std::string;
using boost::gregorian::date;


struct BasicTradeInfo
{
	string tradeID;
	string underlying;
	double strike;
	date expiryDate;
};
