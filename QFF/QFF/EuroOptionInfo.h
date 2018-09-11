#pragma once
#include <string>
#include <boost\date_time\gregorian\gregorian.hpp>

using std::string;
using boost::gregorian::date;


struct EuroOptionInfo
{
	EuroOptionInfo() = delete;
	string tradeID;
	string underlying;
	double strike;
	date expiryDate;
	double timeToMaturity;

};