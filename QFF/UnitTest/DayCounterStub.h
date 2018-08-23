#pragma once
#include <IDayCounter.h>
#include "gmock/gmock.h"

class DayCounterStub : public IDayCounter {
public:
	MOCK_CONST_METHOD2(countDayBetween, double(date, date));
	MOCK_CONST_METHOD2(calculateYearFraction, double(date, date));
};

