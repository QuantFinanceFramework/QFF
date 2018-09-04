#pragma once
#include "ICashFlow.h"
#include <boost/date_time/gregorian/gregorian.hpp>
#include "IDayCounter.h"
#include <memory>
#include <string>

using boost::gregorian::date;
using std::shared_ptr;
using std::string;

class Coupon :
	public ICashFlow
{
public:
	Coupon(double notional, date paymentDate, date accrualStartDate, date accrualEndDate,
		shared_ptr<IDayCounter> dayCounter, string discountCurveName);

	~Coupon() = default;

	date getPaymentDate() const final;

protected:
	double calculateAccrualPeriod() const;

	double m_notional;
	date m_paymentDate;
	date m_accrualStartDate;
	date m_accrualEndDate;
	shared_ptr<IDayCounter> m_dayCounter;
	string m_discountCurveName;
};

