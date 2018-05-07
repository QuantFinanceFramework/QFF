#include "gtest/gtest.h"
#include "pch.h"

TEST(BlackScholesPricerTest, TestEvaluate) {
	auto pricer = BlackScholesPricer();
	auto marketData = MarketData();
	auto currency = ICurrency();
	auto result = pricer.evaluate(marketData, currency);
	EXPECT_EQ(result, 0.0);
}