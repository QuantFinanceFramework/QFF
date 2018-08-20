#pragma once
#include "Coupon.h"
class FixedRateCoupon :
	public Coupon
{
public:
	FixedRateCoupon(double notional, date paymentDate, date accrualStartDate, date accrualEndDate,
		shared_ptr<IDayCounter> dayCounter, string discountCurveName, double rate);
	~FixedRateCoupon() = default;

	double evaluate(const IMarketData & marketData, const ICurrency& currency) const override;
	double getPaymentAmount() const;

private:
	double m_rate;

};

