#include "Coupon.h"

Coupon::Coupon(double notional, 
	date paymentDate, 
	date accrualStartDate, 
	date accrualEndDate, 
	shared_ptr<IDayCounter> dayCounter, 
	string discountCurveName) : 
	m_notional{ notional }, m_paymentDate{ paymentDate }, m_accrualStartDate{ accrualStartDate }, 
	m_accrualEndDate{ accrualEndDate }, m_dayCounter{ dayCounter }, m_discountCurveName{ discountCurveName }{}

date Coupon::getPaymentDate() const
{
	return m_paymentDate;
}

double Coupon::calculateAccrualPeriod() const
{
	return m_dayCounter->calculateYearFraction(m_accrualStartDate, m_accrualEndDate);
}
