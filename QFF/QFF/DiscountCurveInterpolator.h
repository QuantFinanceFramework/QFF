#pragma once
#include <map>
#include <functional>

using std::map;
using std::function;

class DiscountCurveInterpolator
{
public:
	DiscountCurveInterpolator(function<double(const double &, const map<double, double> &)> interpolFunc);
	virtual ~DiscountCurveInterpolator() = default;

	double interpol(const double & queryTime, const map<double, double> & data) const;

private:
	function<double(const double &, const map<double, double> &)> m_interpolFunc;
};
