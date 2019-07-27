#include <Actual365.h>
#include <CurveInterpolator.h>
#include <DiscountFactorCurve.h>
#include <Interpolation.h>
#include <vector>
#include "gtest/gtest.h"

using namespace qff;

class DiscountFactorCurveTestFixture : public ::testing::Test {
 protected:
  DiscountFactorCurve* libor_3m_ = nullptr;

  void SetUp() override {
    date curve_date{2019, 3, 19};
    std::vector<date> dates{
        date(2019, 3, 19),  date(2019, 6, 21),  date(2019, 9, 19),
        date(2019, 12, 18), date(2020, 3, 18),  date(2020, 6, 18),
        date(2020, 9, 17),  date(2020, 12, 16), date(2021, 3, 16),
        date(2021, 6, 17),  date(2021, 9, 16),  date(2021, 12, 15),
        date(2022, 3, 15),  date(2022, 6, 16),  date(2023, 3, 21),
        date(2024, 3, 21),  date(2025, 3, 24),  date(2026, 3, 23),
        date(2027, 3, 22),  date(2028, 3, 21),  date(2029, 3, 21),
        date(2031, 3, 24),  date(2034, 3, 21),  date(2039, 3, 21),
        date(2044, 3, 21),  date(2049, 3, 22),  date(2059, 3, 24)};
    std::vector<double> discount_factors{1.0,
                                         0.993172346289134,
                                         0.986730317128156,
                                         0.980391842332044,
                                         0.974001395636903,
                                         0.967782724934433,
                                         0.961832903220393,
                                         0.956118564034139,
                                         0.95046465375642,
                                         0.944760202885109,
                                         0.939229321848812,
                                         0.933820408371596,
                                         0.92841427525713,
                                         0.922845222358382,
                                         0.906345084946026,
                                         0.884302060331126,
                                         0.861608174750851,
                                         0.839004876455134,
                                         0.816164924750594,
                                         0.793202094041263,
                                         0.770383945758586,
                                         0.725448546172813,
                                         0.66360595605489,
                                         0.573273128498543,
                                         0.497554196810825,
                                         0.432445222643056,
                                         0.327738486248511};

    CurveInterpolator interpolator{LogLinearInterpol,
                                   LogLinearExtrapol};
    Actual365 day_counter{};
    libor_3m_ =
        new DiscountFactorCurve{curve_date, std::move(dates), discount_factors,
                                interpolator, day_counter};
  }
  void TearDown() override { delete libor_3m_; }
};

TEST_F(DiscountFactorCurveTestFixture, GetDiscountFactor_Pillar) {
  EXPECT_NEAR(libor_3m_->GetDiscountFactor(date(2049, 3, 22)), 0.432445222643056,
              0.0000001);
}

TEST_F(DiscountFactorCurveTestFixture, GetDiscountFactor_Interpol) {
  EXPECT_NEAR(libor_3m_->GetDiscountFactor(date(2023, 5, 15)), 0.902997858382675,
              0.0000001);
}

TEST_F(DiscountFactorCurveTestFixture, GetDiscountFactor_Extrapol) {
  EXPECT_NEAR(libor_3m_->GetDiscountFactor(date(2060, 5, 15)), 0.317507394906338,
              0.0000001);
}