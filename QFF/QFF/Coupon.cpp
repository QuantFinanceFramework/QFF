#include "Coupon.h"

Coupon::Coupon(double notional, const string& currencyCode, date paymentDate, date accrualStartDate,
	date accrualEndDate, const IDayCounter& dayCounter) : notional_{ notional }, 
	currencyCode_{ currencyCode }, paymentDate_{ paymentDate },	accrualStartDate_{ accrualStartDate },
	accrualEndDate_{ accrualEndDate }{dayCounter_ = dayCounter.clone(); }

string Coupon::getCurrency() const
{
	return currencyCode_;
}

date Coupon::getPaymentDate() const
{
	return paymentDate_;
}

double Coupon::calculateAccrualFactor() const
{
	return dayCounter_->calculateYearFraction(accrualStartDate_, accrualEndDate_);
}

