#include "gtest/gtest.h"
#include <MarketData.h>
#include <vector>
#include <SwapLeg.h>
#include "CurrencyStub.h"
#include "CashFlowStub.h"

using namespace testing;
using std::vector;

TEST(SwapLegTest, EvaluateTest) {
	MarketData data;
	CurrencyStub currency{};
	CashFlowStub dummyCashFlow1{};
	CashFlowStub dummyCashFlow2{};
	CashFlowStub dummyCashFlow3{};
	SwapLeg swapLeg{ vector<ICashFlow*>{&dummyCashFlow1, &dummyCashFlow2, &dummyCashFlow3} };

	ON_CALL(dummyCashFlow1, evaluate(_, _)).WillByDefault(Return(1.0));
	ON_CALL(dummyCashFlow2, evaluate(_, _)).WillByDefault(Return(2.0));
	ON_CALL(dummyCashFlow3, evaluate(_, _)).WillByDefault(Return(2.5));

	EXPECT_EQ(swapLeg.evaluate(data, currency), 5.5);
}