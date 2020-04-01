#include <BlackScholesFormula.h>
#include "../Aad/aad_all.h"
#include "gtest/gtest.h"

using namespace qff_a;
using namespace aad;

TEST(BlackScholesFormulaTest, BlackScholesFormula_double) {
  const auto result = BlackScholesFormula(100.0, 100.0, 1.0, 1.0, 0.2, "call");
  EXPECT_NEAR(result, 7.9656, 0.0001);
}

TEST(BlackScholesFormulaTest, BlackScholesFormula_a_double) {
  const auto result = BlackScholesFormula(a_double(100.0), 110.0, a_double(1.0), 1.5, a_double(0.3), "put").value();
  EXPECT_NEAR(result, 20.8107, 0.0001);
}

TEST(BlackScholesFormulaTest, BlackScholesImpliedVolatility_call) {
  const auto result =
      BlackScholesImpliedVolatility(7.9656, 100.0, 100.0, 1.0, 1.0, "call");
  EXPECT_NEAR(result, 0.20, 0.0001);
}

TEST(BlackScholesFormulaTest, BlackScholesImpliedVolatility_put) {
  const auto result =
      BlackScholesImpliedVolatility(20.8107, 100.0, 110.0, 1.0, 1.5, "put");
  EXPECT_NEAR(result, 0.30, 0.0001);
}