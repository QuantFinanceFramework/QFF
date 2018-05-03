#include "gtest/gtest.h"
#include "pch.h"
#include <BlackScholesPricer.h>

TEST(BlackScholesPricerTest, TestEvaluate) {
	auto pricer = BlackScholesPricer();
	auto result = pricer.evaluate();
	EXPECT_EQ(result, 0.0);
}