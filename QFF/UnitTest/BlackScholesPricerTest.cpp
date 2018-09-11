#pragma once
#include "gtest\gtest.h"
#include <BlackScholesPricer.h>
#include <boost\date_time\gregorian\gregorian.hpp>
#include "CurrencyStub.h"
#include "MarketDataStub.h"

using namespace testing;

TEST(BlackScholesPricerTest, EvaluateCallTest) {

	MarketDataStub data{};
	EuroOptionInfo info{ "Dummy_Trade", "Brent", 105.0, date(2002,12,10), 0.05479};
	CurrencyStub currency{};

	ON_CALL(data, getDiscountFactor(_, _)).WillByDefault(Return(0.9994));
	ON_CALL(data, getSpot(_)).WillByDefault(Return(100.0));
	ON_CALL(data, getVolatility(_, _, _)).WillByDefault(Return(0.3815));

	auto pricer = BlackScholesPricer{};
	auto result = pricer.evaluate(data, info, "call", currency);

	EXPECT_NEAR(result, 1.70, 0.001);

}

TEST(BlackScholesPricerTest, EvaluatePutTest) {

	MarketDataStub data{};
	EuroOptionInfo info{ "Dummy_Trade", "Brent", 105.0, date(2002,12,10), 0.05479 };
	CurrencyStub currency{};

	ON_CALL(data, getDiscountFactor(_, _)).WillByDefault(Return(0.9994));
	ON_CALL(data, getSpot(_)).WillByDefault(Return(100.0));
	ON_CALL(data, getVolatility(_, _, _)).WillByDefault(Return(0.3815));

	auto pricer = BlackScholesPricer{};
	auto result = pricer.evaluate(data, info, "put", currency);

	EXPECT_NEAR(result, 6.636, 0.001);

}

TEST(BlackScholesPricerTest, EvaluateErrorTest) {

	MarketDataStub data{};
	EuroOptionInfo info{ "Dummy_Trade", "Brent", 50, date(2002,12,10), 1 };
	CurrencyStub currency{};

	ON_CALL(data, getDiscountFactor(_, _)).WillByDefault(Return(1.0));
	ON_CALL(data, getForwardRateProjection(_, _)).WillByDefault(Return(1.0));
	ON_CALL(data, getSpot(_)).WillByDefault(Return(1.0));
	ON_CALL(data, getForward(_, _)).WillByDefault(Return(1.0));
	ON_CALL(data, getVolatility(_, _, _)).WillByDefault(Return(1.0));

	auto pricer = BlackScholesPricer{};
	EXPECT_THROW(pricer.evaluate(data, info, "swap", currency),std::invalid_argument);
}