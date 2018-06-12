#pragma once
#include "gtest\gtest.h"
#include <Black76Pricer.h>
#include <boost\date_time\gregorian\gregorian.hpp>
#include "CurrencyStub.h"

using namespace testing;

TEST(Black76PricerTest, EvaluateCallTest) {
  
	MarketData data{ 50, 0.25, 0.1, 0.0 };
	BasicTradeInfo info{ "Dummy_Trade", "Brent", 50, date(2002,12,10), 1 };
	CurrencyStub currency{};
	auto pricer = Black76Pricer{};
	auto result = pricer.evaluate(data, info, "call", currency);

	EXPECT_NEAR(result, 4.5005,0.0001);
  
}

TEST(Black76PricerTest, EvaluatePutTest) {

	MarketData data{ 50, 0.25, 0.1, 0.0 };
	BasicTradeInfo info{ "Dummy_Trade", "Brent", 50, date(2002,12,10), 1 };
	CurrencyStub currency{};
	auto pricer = Black76Pricer{};
	auto result = pricer.evaluate(data, info, "put", currency);

	EXPECT_NEAR(result, 4.5005,0.0001);

}

TEST(Black76PricerTest, EvaluateErrorTest) {

	MarketData data{ 50, 0.25, 0.1, 0.0 };
	BasicTradeInfo info{ "Dummy_Trade", "Brent", 50, date(2002,12,10), 1 };
	CurrencyStub currency{};
	auto pricer = Black76Pricer{};
	auto result = pricer.evaluate(data, info, "swap", currency);

	//EXPECT_THROW(result,std::invalid_argument);
	EXPECT_EQ(result, 0);
}
