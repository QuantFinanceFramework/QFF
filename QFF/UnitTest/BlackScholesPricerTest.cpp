#pragma once
#include "gtest\gtest.h"
#include <BlackScholesPricer.h>
#include <boost\date_time\gregorian\gregorian.hpp>
#include "CurrencyStub.h"

using namespace testing;

TEST(BlackScholesPricerTest, EvaluateCallTest) {
  
	MarketData data{ 50, 0.25, 0.1, 0.0 };
	BasicTradeInfo info{ "Dummy_Trade", "Brent", 50, date(2002,12,10), 1, "call"};
	CurrencyStub currency{};
	auto pricer = BlackScholesPricer{};
	auto result = pricer.evaluate(data, info, currency);

	EXPECT_EQ(result, 4.5005);
  
}

TEST(BlackScholesPricerTest, EvaluatePutTest) {

	MarketData data{ 50, 0.25, 0.1, 0.0 };
	BasicTradeInfo info{ "Dummy_Trade", "Brent", 50, date(2002,12,10), 1, "put" };
	CurrencyStub currency{};
	auto pricer = BlackScholesPricer{};
	auto result = pricer.evaluate(data, info, currency);

	EXPECT_EQ(result, 4.5005);

}
