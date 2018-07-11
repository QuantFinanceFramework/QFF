#pragma once
#include <vector>
#include <boost\date_time\gregorian\gregorian.hpp>
#include "IInterpolator.h"

using std::vector;
using boost::gregorian::date;

class FXCurve
{
public:
	FXCurve() = delete;
	virtual ~FXCurve() = default;
	double getFXRate(date date) const;

private:
	vector<date> m_dates;
	vector<double> m_values;
	IInterpolator* m_interpolator;
};
