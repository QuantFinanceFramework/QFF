#include <DiscountCurve.h>
#include <DiscountCurveInterpolator.h>
#include <functional>
#include <LinearInterpolator.h>
#include <LogLinearInterpolator.h>
#include <Actual365DayCounter.h>
#include <vector>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <memory>
#include <SobolNormalRsg.h>
#include <GaussianShortRate1FProcess.h>
#include <ConstantParameter.h>
#include <EconomicScenarioGenerator.h>

using std::function;
using std::vector;
using boost::gregorian::date;
using std::make_shared;
using std::make_unique;

int main()
{
	auto ll = DiscountCurveInterpolator{ logLinearInterpol };
	auto dates = vector<date>{ date{2018, 3, 21}, date{2019, 3, 21}, date{2020, 3, 21}, date{2030, 3, 21} };
	auto df = vector<double>{ 1, 0.99, 0.98, 0.8 };
	auto dc = DiscountCurve{ dates, df, ll, make_shared<Actual365DayCounter>() };
	auto gsr = make_shared<GaussianShortRate1FProcess>( make_shared<DiscountCurve>(dates, df, ll, make_shared<Actual365DayCounter>()),
		make_unique<ConstantParameter>(0.001),
		make_unique<ConstantParameter>(0.2),
		make_unique<GaussianShortRate1FProcess::EulerScheme>());
	vector<double> timeGrid{ 1.0, 2.0, 4.0, 5.0 };
	EconomicScenarioGenerator esg { 0.0, gsr, timeGrid, "Sobol" };
	auto result = esg.generateScenarioSet(1000000);

	return EXIT_SUCCESS;
}