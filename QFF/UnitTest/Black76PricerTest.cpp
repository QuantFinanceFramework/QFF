#pragma once
#include "gtest\gtest.h"
#include <Black76Pricer.h>
#include <boost\date_time\gregorian\gregorian.hpp>
#include "CurrencyStub.h"
#include "MarketDataStub.h"

using namespace testing;

TEST(Black76PricerTest, EvaluateCallTest) {
  
	MarketDataStub data{};
	BasicTradeInfo info{ "Dummy_Trade", "Brent", 50, date(2002,12,10), 1 };
	CurrencyStub currency{};
	
	ON_CALL(data, getDiscountFactor(_, _)).WillByDefault(Return(1.0));
	ON_CALL(data, getForwardRateProjection(_, _)).WillByDefault(Return(1.0));
	ON_CALL(data, getSpot(_)).WillByDefault(Return(1.0));
	ON_CALL(data, getForward(_, _)).WillByDefault(Return(1.0));
	ON_CALL(data, getVolatility(_, _, _)).WillByDefault(Return(1.0));

	auto pricer = Black76Pricer{};
	auto result = pricer.evaluate(data, info, "call", currency);

	EXPECT_NEAR(result, 4.5005,0.0001);
  
}

TEST(Black76PricerTest, EvaluatePutTest) {

	MarketDataStub data{};
	BasicTradeInfo info{ "Dummy_Trade", "Brent", 50, date(2002,12,10), 1 };
	CurrencyStub currency{};

	ON_CALL(data, getDiscountFactor(_, _)).WillByDefault(Return(1.0));
	ON_CALL(data, getForwardRateProjection(_, _)).WillByDefault(Return(1.0));
	ON_CALL(data, getSpot(_)).WillByDefault(Return(1.0));
	ON_CALL(data, getForward(_, _)).WillByDefault(Return(1.0));
	ON_CALL(data, getVolatility(_, _, _)).WillByDefault(Return(1.0));

	auto pricer = Black76Pricer{};
	auto result = pricer.evaluate(data, info, "put", currency);

	EXPECT_NEAR(result, 4.5005,0.0001);

}

TEST(Black76PricerTest, EvaluateErrorTest) {

	MarketDataStub data{};
	BasicTradeInfo info{ "Dummy_Trade", "Brent", 50, date(2002,12,10), 1 };
	CurrencyStub currency{};

	ON_CALL(data, getDiscountFactor(_, _)).WillByDefault(Return(1.0));
	ON_CALL(data, getForwardRateProjection(_, _)).WillByDefault(Return(1.0));
	ON_CALL(data, getSpot(_)).WillByDefault(Return(1.0));
	ON_CALL(data, getForward(_, _)).WillByDefault(Return(1.0));
	ON_CALL(data, getVolatility(_, _, _)).WillByDefault(Return(1.0));

	auto pricer = Black76Pricer{};
	EXPECT_THROW(pricer.evaluate(data, info, "swap", currency), std::invalid_argument); 
}
