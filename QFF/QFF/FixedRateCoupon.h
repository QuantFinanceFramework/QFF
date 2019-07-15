#pragma once
#include "Coupon.h"

class FixedRateCoupon :
	public Coupon
{
public:
	FixedRateCoupon() = default;
	FixedRateCoupon(double notional, date paymentDate, date accrualStartDate, date accrualEndDate,
		const IDayCounter& dayCounter, double rate);

	~FixedRateCoupon() = default;

	double getPaymentAmount(const IMarketData& marketData) const override;

private:
	double rate_;

};

