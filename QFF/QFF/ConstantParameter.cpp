#include "ConstantParameter.h"

ConstantParameter::ConstantParameter(double value) : m_value{ value }, m_valueSquare{ value*value }{}

double ConstantParameter::operator[](double time) const
{
	return m_value;
}

double ConstantParameter::integral(double time1, double time2) const
{
	return m_value*(time2-time1);
}

double ConstantParameter::integralSquare(double time1, double time2) const
{
	return m_valueSquare*(time2-time1);
}
