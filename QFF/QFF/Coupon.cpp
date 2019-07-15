#include "Coupon.h"

Coupon::Coupon(double notional, date paymentDate, date accrualStartDate, date accrualEndDate,
	const IDayCounter& dayCounter) : notional_{ notional }, paymentDate_{ paymentDate },
	accrualStartDate_{ accrualStartDate }, accrualEndDate_{ accrualEndDate }{
	dayCounter_ = dayCounter.clone(); }

double Coupon::calculateAccrualFactor() const
{
	return dayCounter_->calculateYearFraction(accrualStartDate_, accrualEndDate_);
}

