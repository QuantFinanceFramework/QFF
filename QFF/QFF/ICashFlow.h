#pragma once
#include "IInstrument.h"
#include <boost/date_time/gregorian/gregorian.hpp>

using boost::gregorian::date;

class ICashFlow : 
	public IInstrument
{
public:
	ICashFlow() = delete;
	virtual ~ICashFlow() = default;
	virtual date getPaymentDate() const = 0;
};

