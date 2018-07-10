#pragma once
#include <ICashFlow.h>
#include "gmock\gmock.h"

class CashFlowStub : public ICashFlow {
public:
	MOCK_CONST_METHOD2(evaluate, double(const MarketData&, const ICurrency&));
};
