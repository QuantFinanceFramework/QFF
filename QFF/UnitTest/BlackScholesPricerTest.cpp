#pragma once
#include "gtest\gtest.h"
#include <BlackScholesPricer.h>
#include <boost\date_time\gregorian\gregorian.hpp>
#include "CurrencyStub.h"

using namespace testing;

TEST(BlackScholesPricerTest, EvaluateCallTest) {

	MarketData data{ 50, 0.25, 0.1, 0.0 };
	BasicTradeInfo info{ "Dummy_Trade", "Brent", 50, date(2002,12,10), 1 };
	CurrencyStub currency{};
	auto pricer = BlackScholesPricer{};
	auto result = pricer.evaluate(data, info, "call", currency);

	EXPECT_NEAR(result, 7.4879, 0.0001);

}

TEST(BlackScholesPricerTest, EvaluatePutTest) {

	MarketData data{ 50, 0.25, 0.1, 0.0 };
	BasicTradeInfo info{ "Dummy_Trade", "Brent", 50, date(2002,12,10), 1 };
	CurrencyStub currency{};
	auto pricer = BlackScholesPricer{};
	auto result = pricer.evaluate(data, info, "put", currency);

	EXPECT_NEAR(result, 2.7298, 0.0001);

}

TEST(BlackScholesPricerTest, EvaluateErrorTest) {

	MarketData data{ 50, 0.25, 0.1, 0.0 };
	BasicTradeInfo info{ "Dummy_Trade", "Brent", 50, date(2002,12,10), 1 };
	CurrencyStub currency{};
	auto pricer = BlackScholesPricer{};
	EXPECT_THROW(pricer.evaluate(data, info, "swap", currency),std::invalid_argument);
}