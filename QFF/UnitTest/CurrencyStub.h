#pragma once
#include <ICurrency.h>
#include "gmock\gmock.h"

class CurrencyStub : public ICurrency {
public:
	MOCK_CONST_METHOD0(getCurrency, string());
};