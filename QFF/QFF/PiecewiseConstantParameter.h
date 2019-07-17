#pragma once
#include "IParameter.h"
#include <map>

namespace qff {
	using std::map;

	class PiecewiseConstantParameter :
		public IParameter
	{
	public:
		PiecewiseConstantParameter() = default;
		PiecewiseConstantParameter(const map<double, double>& value);

		~PiecewiseConstantParameter() = default;

		double operator[](double time) const override;
		double integral(double time1, double time2) const override;
		double integralSquare(double time1, double time2) const override;

	private:
		map<double, double> m_value;
	};
}