#pragma once
#include "gtest\gtest.h"
#include <TurnbullWakemanPricer.h>
#include <boost\date_time\gregorian\gregorian.hpp>
#include "CurrencyStub.h"
#include "MarketDataStub.h"

using namespace testing;

TEST(TurnbullWakemanPricerTest, EvaluateTest) {

	MarketDataStub data{};
	BasicTradeInfo info{ "Dummy_Trade", "Brent", 50, date(2002,12,10), 1};
	CurrencyStub currency{};

	ON_CALL(data, getDiscountFactor(_, _)).WillByDefault(Return(1.0));
	ON_CALL(data, getForwardRateProjection(_, _)).WillByDefault(Return(1.0));
	ON_CALL(data, getSpot(_)).WillByDefault(Return(1.0));
	ON_CALL(data, getForward(_, _)).WillByDefault(Return(1.0));
	ON_CALL(data, getVolatility(_, _, _)).WillByDefault(Return(1.0));

	auto pricer = TurnbullWakemanPricer{};
	auto result = pricer.evaluate(data, info, currency);

	EXPECT_EQ(result, 0);

}