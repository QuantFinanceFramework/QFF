#include "PiecewiseConstantParameter.h"
#include <cmath>

PiecewiseConstantParameter::PiecewiseConstantParameter(const map<double, double>& value) :m_value{value}{}

double PiecewiseConstantParameter::operator[](double time) const
{
	if (time < m_value.begin()->first) return 0.0;
	return std::prev(m_value.upper_bound(time))->second;
}

double PiecewiseConstantParameter::integral(double time1, double time2) const
{
	if (time1 < m_value.begin()->first || time2 < m_value.begin()->first) return 0.0;

	double endTime = 0.0;
	double startTime = time1;
	double result = 0.0;

	for (auto iter = prev(m_value.upper_bound(time1)); iter != m_value.upper_bound(time2); ++iter)
	{
		if (next(iter) == m_value.upper_bound(time2))
			endTime = time2;
		else
			endTime = next(iter)->first;

		result += iter->second * (endTime - startTime);
		startTime = endTime;
	}

	return result;
}

double PiecewiseConstantParameter::integralSquare(double time1, double time2) const
{
	if (time1 < m_value.begin()->first || time2 < m_value.begin()->first) return 0.0;

	double endTime = 0.0;
	double startTime = time1;
	double result = 0.0;

	for (auto iter = prev(m_value.upper_bound(time1)); iter != m_value.upper_bound(time2); ++iter)
	{
		if (next(iter) == m_value.upper_bound(time2))
			endTime = time2;
		else
			endTime = next(iter)->first;

		result += std::pow(iter->second, 2) * (endTime - startTime);
		startTime = endTime;
	}

	return result;
}

