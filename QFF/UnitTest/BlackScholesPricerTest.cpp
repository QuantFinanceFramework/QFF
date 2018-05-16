#pragma once
#include "gtest\gtest.h"
#include <ICurrency.h>
#include <BlackScholesPricer.h>
#include <boost\date_time\gregorian\gregorian.hpp>

class CurrencyStub :
	public ICurrency
{
};

TEST(PricerTest, EvaluateTest) {
  
	MarketData data{ 0.0, 0.0, 0.0 };
	BasicTradeInfo info{ "Dummy_Trade", "Brent", 50, date (2002,12,10) };
	auto currency = CurrencyStub{};
	auto pricer = BlackScholesPricer{};
	auto result = pricer.evaluate(data, info, currency);

	EXPECT_EQ(result, 0);
  
}