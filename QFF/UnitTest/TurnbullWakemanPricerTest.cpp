#pragma once
#include "gtest\gtest.h"
#include <TurnbullWakemanPricer.h>
#include <boost\date_time\gregorian\gregorian.hpp>
#include "CurrencyStub.h"

using namespace testing;

TEST(TurnbullWakemanPricerTest, EvaluateTest) {

	MarketData data{ 0.0, 0.0, 0.0 };
	BasicTradeInfo info{ "Dummy_Trade", "Brent", 50, date(2002,12,10) };
	CurrencyStub currency{};
	auto pricer = TurnbullWakemanPricer{};
	auto result = pricer.evaluate(data, info, currency);

	EXPECT_EQ(result, 0);

}