#include "FloatingRateCoupon.h"

FloatingRateCoupon::FloatingRateCoupon(double notional,
	date paymentDate,
	date accrualStartDate,
	date accrualEndDate,
	shared_ptr<IDayCounter> dayCounter,
	string discountCurveName,
	string projectionCurveName,
	date fixingDate,
	double leverage,
	double spread) :Coupon(notional, paymentDate, accrualStartDate, accrualEndDate, dayCounter, discountCurveName),
	m_projectionCurveName{ projectionCurveName },
	m_fixingDate{ fixingDate },
	m_leverage{ leverage },
	m_spread{ spread } {}

double FloatingRateCoupon::evaluate(const IMarketData & marketData, const ICurrency & currency) const
{
	return getPaymentAmount(marketData) * marketData.getDiscountFactor(m_discountCurveName, m_paymentDate);
}

double FloatingRateCoupon::getPaymentAmount(const IMarketData & marketData) const
{
	return m_notional * getRate(marketData) * calculateAccrualPeriod();
}

double FloatingRateCoupon::getRate(const IMarketData & marketData) const
{
	return marketData.getForwardRateProjection(m_projectionCurveName, m_fixingDate) * m_leverage + m_spread;
}


