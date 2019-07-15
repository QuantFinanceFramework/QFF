#pragma once

#include <boost/date_time/gregorian/gregorian.hpp>

using boost::gregorian::date;

class ICashFlow
{
public:
	ICashFlow() = default;
	virtual ~ICashFlow() = default;

	virtual double getAmount() const = 0;
	virtual date getPaymentDate() const = 0;
};

