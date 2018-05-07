#include "gtest/gtest.h"
#include "pch.h"

TEST(TurnbullWakemanPricerTest, TestEvaluate) {
	auto pricer = TurnbullWakemanPricer();
	auto marketData = MarketData();
	auto currency = ICurrency();
	auto result = pricer.evaluate(marketData, currency);
	EXPECT_EQ(result, 0.0);
}