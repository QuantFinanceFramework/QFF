#pragma once
#include "ICashFlow.h"
#include <boost/date_time/gregorian/gregorian.hpp>
#include "IDayCounter.h"
#include <memory>
#include <string>

using boost::gregorian::date;
using std::unique_ptr;
using std::string;

class Coupon :
	public ICashFlow
{
public:
	Coupon(double notional, date paymentDate, date accrualStartDate, date accrualEndDate,
		const IDayCounter& dayCounter);
	~Coupon() = default;

protected:
	double calculateAccrualFactor() const;

	double notional_;
	date paymentDate_;
	date accrualStartDate_;
	date accrualEndDate_;
	unique_ptr<IDayCounter> dayCounter_;
};

