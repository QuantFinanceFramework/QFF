#include "gtest/gtest.h"
#include <EuropeanOption.h>
#include <Black76Pricer.h>
#include <MarketData.h>
#include <Aud.h>
#include "MarketDataStub.h"

using namespace testing;

TEST(EuropeanOptionTest, EvaluateTest) {
	MarketDataStub data{};
	EuroOptionInfo info{ "Dummy_Trade", "Copper", 2100.0, date(2002,12,10), 0.084935 };
	EuropeanOption instrument{ info, "call", std::make_shared<Black76Pricer>()};

	ON_CALL(data, getDiscountFactor(_, _)).WillByDefault(Return(0.993846));
	ON_CALL(data, getForward(_, _)).WillByDefault(Return(2006.0));
	ON_CALL(data, getVolatility(_, _, _)).WillByDefault(Return(0.35));

	EXPECT_NEAR(instrument.evaluate(data, Aud{}), 44.50, 0.001);
}