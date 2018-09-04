#include "gtest/gtest.h"
#include <Swap.h>
#include "CashFlowStub.h"
#include "CurrencyStub.h"
#include "MarketDataStub.h"
#include "DayCounterStub.h"
#include <boost/date_time/gregorian/gregorian.hpp>
#include <memory>

using namespace testing;
using std::shared_ptr;
using std::make_shared;

TEST(SwapTest, EvaluateTest) {
	MarketDataStub data{};
	CurrencyStub currency{};
	auto pDummyCashFlow1 = std::make_unique<CashFlowStub>();
	auto pDummyCashFlow2 = std::make_unique<CashFlowStub>();
	auto pDummyCashFlow3 = std::make_unique<CashFlowStub>();

	ON_CALL(*pDummyCashFlow1, evaluate(_, _)).WillByDefault(Return(1.0));
	ON_CALL(*pDummyCashFlow2, evaluate(_, _)).WillByDefault(Return(2.0));
	ON_CALL(*pDummyCashFlow3, evaluate(_, _)).WillByDefault(Return(2.5));

	vector<unique_ptr<ICashFlow>> cashFlowVector1;
	cashFlowVector1.emplace_back(move(pDummyCashFlow1));
	cashFlowVector1.emplace_back(move(pDummyCashFlow2));

	vector<unique_ptr<ICashFlow>> cashFlowVector2;
	cashFlowVector2.emplace_back(move(pDummyCashFlow3));

	Swap swap{ CashFlowCollection { move(cashFlowVector1)},
		CashFlowCollection{ move(cashFlowVector2) } };

	EXPECT_EQ(swap.evaluate(data, currency), 0.5);
}