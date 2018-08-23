#include "gtest/gtest.h"
#include <FixedRateCoupon.h>
#include "CurrencyStub.h"
#include "MarketDataStub.h"
#include "DayCounterStub.h"
#include <boost/date_time/gregorian/gregorian.hpp>
#include <memory>

using namespace testing;
using std::shared_ptr;
using std::make_shared;

TEST(FixedRateCouponTest, EvaluateTest) {
	MarketDataStub data{};
	ON_CALL(data, getDiscountFactor(_, _)).WillByDefault(Return(1.0));
	CurrencyStub currency{};
	auto dayCounter = make_shared<DayCounterStub>();
	ON_CALL(*dayCounter, calculateYearFraction(_, _)).WillByDefault(Return(0.25));
	FixedRateCoupon coupon{ 100.0, date(2019,9,20), date(2019,6,20), date(2019,9,20), dayCounter, "AUD_Std", 0.05 };
	EXPECT_NEAR(coupon.evaluate(data, currency), 1.25, 0.0001);
}