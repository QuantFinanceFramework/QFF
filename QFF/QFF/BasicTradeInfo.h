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
	//need to work out how to deal with dates
	date expiryDate; 
	
	//not sure best way to do this so here for now
	double timeToMaturity;
	
};
