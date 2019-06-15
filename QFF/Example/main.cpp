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
#include <BlackScholesProcess.h>
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
	auto bs = make_shared<BlackScholesProcess>( 
		make_unique<ConstantParameter>(0.001),
		make_unique<ConstantParameter>(0.2),
		make_unique<BlackScholesProcess::EulerScheme>());
	vector<double> timeGrid{ 0.0, 2.0, 4.0, 5.0 };
	EconomicScenarioGenerator esg{ {100.0}, bs, timeGrid, "Pseudo" };
	auto result = esg.generateScenarioSet(100);

	return EXIT_SUCCESS;
}