#include "FixedRateCoupon.h"

FixedRateCoupon::FixedRateCoupon(double notional, 
	date paymentDate, 
	date accrualStartDate, 
	date accrualEndDate, 
	shared_ptr<IDayCounter> dayCounter, 
	string discountCurveName, 
	double rate): 
	Coupon(notional, paymentDate, accrualStartDate, accrualEndDate, dayCounter, discountCurveName), m_rate{ rate }{}

double FixedRateCoupon::evaluate(const IMarketData & marketData, const ICurrency & currency) const
{
	return getPaymentAmount() * marketData.getDiscountFactor(m_discountCurveName, m_paymentDate);
}

date FixedRateCoupon::getPaymentDate() const
{
	return m_paymentDate;
}

double FixedRateCoupon::getPaymentAmount() const
{
	return m_notional * m_rate * calculateAccrualPeriod();
}

