#pragma once
#include <IInstrument.h>
#include "gmock\gmock.h"

class InstrumentStub : public IInstrument {
public:
	MOCK_CONST_METHOD2(evaluate, double(const IMarketData&, const ICurrency&));
};
