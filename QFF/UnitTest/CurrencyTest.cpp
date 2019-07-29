#include <Currency.h>
#include "gtest/gtest.h"

using namespace qff;

TEST(CurrencyTest, Plus) {
	const Currency usd1{"USD", 100.0};
	const Currency usd2{"USD", 100.0};
	const auto usd3 = usd1 + usd2;
  EXPECT_NEAR(usd3.amount, 200.0, 0.0001);
}

TEST(CurrencyTest, Minus) {
  const Currency usd1{"USD", 100.0};
  const Currency usd2{"USD", 100.0};
  const auto usd3 = usd1 - usd2;
  EXPECT_NEAR(usd3.amount, 0.0, 0.0001);
}

TEST(CurrencyTest, Plus_different_currency) {
  const Currency usd{"USD", 100.0};
  const Currency aud{"AUD", 100.0};
  EXPECT_THROW(usd + aud, std::logic_error);
}