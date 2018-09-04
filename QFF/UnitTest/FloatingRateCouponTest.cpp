#include "gtest/gtest.h"
#include <FloatingRateCoupon.h>
#include "CurrencyStub.h"
#include "MarketDataStub.h"
#include "DayCounterStub.h"
#include <boost/date_time/gregorian/gregorian.hpp>
#include <memory>

using namespace testing;
using std::shared_ptr;
using std::make_shared;

TEST(FloatingRateCouponTest, EvaluateTest_OneLeverageZeroSpread) {
	MarketDataStub data{};
	ON_CALL(data, getDiscountFactor(_, _)).WillByDefault(Return(1.0));
	ON_CALL(data, getForwardRateProjection(_, _)).WillByDefault(Return(0.05));
	CurrencyStub currency{};
	auto dayCounter = make_shared<DayCounterStub>();
	ON_CALL(*dayCounter, calculateYearFraction(_, _)).WillByDefault(Return(0.25));
	FloatingRateCoupon coupon{ 100.0, date(2019,9,20), date(2019,6,20), date(2019,9,20), dayCounter, "AUD_3m", "AUD_Std", date(2019,6,18), 1, 0};
	EXPECT_NEAR(coupon.evaluate(data, currency), 1.25, 0.0001);
}

TEST(FloatingRateCouponTest, EvaluateTest_TwoLeverageHundredBPsSpread) {
	MarketDataStub data{};
	ON_CALL(data, getDiscountFactor(_, _)).WillByDefault(Return(1.0));
	ON_CALL(data, getForwardRateProjection(_, _)).WillByDefault(Return(0.05));
	CurrencyStub currency{};
	auto dayCounter = make_shared<DayCounterStub>();
	ON_CALL(*dayCounter, calculateYearFraction(_, _)).WillByDefault(Return(0.25));
	FloatingRateCoupon coupon{ 100.0, date(2019,9,20), date(2019,6,20), date(2019,9,20), dayCounter, "AUD_3m", "AUD_Std", date(2019,6,18), 2, 0.01 };
	EXPECT_NEAR(coupon.evaluate(data, currency), 2.75, 0.0001);
}

TEST(FloatingRateCouponTest, EvaluateTest_OneLeverageNegativeHundredBPsSpread) {
	MarketDataStub data{};
	ON_CALL(data, getDiscountFactor(_, _)).WillByDefault(Return(1.0));
	ON_CALL(data, getForwardRateProjection(_, _)).WillByDefault(Return(0.05));
	CurrencyStub currency{};
	auto dayCounter = make_shared<DayCounterStub>();
	ON_CALL(*dayCounter, calculateYearFraction(_, _)).WillByDefault(Return(0.25));
	FloatingRateCoupon coupon{ 100.0, date(2019,9,20), date(2019,6,20), date(2019,9,20), dayCounter, "AUD_3m", "AUD_Std", date(2019,6,18), 1, -0.01 };
	EXPECT_NEAR(coupon.evaluate(data, currency), 1.0, 0.0001);
}