#pragma once
#include <ICashFlow.h>
#include "gmock\gmock.h"

class CashFlowStub : public ICashFlow {
public:
	MOCK_CONST_METHOD0(getPaymentDate, date());
	MOCK_CONST_METHOD2(evaluate, double(const IMarketData&, const ICurrency&));
};
