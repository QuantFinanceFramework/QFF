#pragma once
#include "gtest\gtest.h"
#include <Black76Pricer.h>
#include <boost\date_time\gregorian\gregorian.hpp>
#include "CurrencyStub.h"
#include "MarketDataStub.h"

using namespace testing;

TEST(Black76PricerTest, EvaluateCallTest) {
  
	MarketDataStub data{};
	EuroOptionInfo info{ "Dummy_Trade", "Copper", 2100.0, date(2002,12,10), 0.084935 };
	CurrencyStub currency{};
	
	ON_CALL(data, getDiscountFactor(_, _)).WillByDefault(Return(0.993846));
	ON_CALL(data, getForward(_, _)).WillByDefault(Return(2006.0));
	ON_CALL(data, getVolatility(_, _, _)).WillByDefault(Return(0.35));

	auto pricer = Black76Pricer{};
	auto result = pricer.evaluate(data, info, "call", currency);
	

	EXPECT_NEAR(result, 44.50,0.001);
  
}

TEST(Black76PricerTest, EvaluatePutTest) {

	MarketDataStub data{};
	EuroOptionInfo info{ "Dummy_Trade", "JKM", 15.0, date(2002,12,10), 0.05 };
	CurrencyStub currency{};

	ON_CALL(data, getDiscountFactor(_, _)).WillByDefault(Return(0.9995));
	ON_CALL(data, getForward(_, _)).WillByDefault(Return(10.0));
	ON_CALL(data, getVolatility(_, _, _)).WillByDefault(Return(0.35));

	auto pricer = Black76Pricer{};
	auto result = pricer.evaluate(data, info, "put", currency);

	EXPECT_NEAR(result, 4.997501,0.001);

}

TEST(Black76PricerTest, EvaluateErrorTest) {

	MarketDataStub data{};
	EuroOptionInfo info{ "Dummy_Trade", "Brent", 50, date(2002,12,10), 1 };
	CurrencyStub currency{};

	ON_CALL(data, getDiscountFactor(_, _)).WillByDefault(Return(1.0));
	ON_CALL(data, getForwardRateProjection(_, _)).WillByDefault(Return(1.0));
	ON_CALL(data, getSpot(_)).WillByDefault(Return(1.0));
	ON_CALL(data, getForward(_, _)).WillByDefault(Return(1.0));
	ON_CALL(data, getVolatility(_, _, _)).WillByDefault(Return(1.0));

	auto pricer = Black76Pricer{};
	EXPECT_THROW(pricer.evaluate(data, info, "swap", currency), std::invalid_argument); 
}
