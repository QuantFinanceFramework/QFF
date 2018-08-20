#pragma once
#include "Coupon.h"
class FloatingRateCoupon :
	public Coupon
{
public:
	FloatingRateCoupon(double notional, date paymentDate, date accrualStartDate, date accrualEndDate,
		shared_ptr<IDayCounter> dayCounter, string discountCurveName, string projectionCurveName, 
		date fixingDate, double leverage, double spread);
	~FloatingRateCoupon() = default;

	double evaluate(const IMarketData & marketData, const ICurrency& currency) const override;
	double getPaymentAmount(const IMarketData & marketData) const;

private:
	double getRate(const IMarketData & marketData) const;

	string m_projectionCurveName;
	date m_fixingDate;
	double m_leverage;
	double m_spread;
};