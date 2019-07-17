#pragma once
#include "IInterpolator.h"
#include <functional>

namespace qff {
	using std::function;

	class CurveInterpolator :
		public IInterpolator
	{
	public:
		CurveInterpolator() = default;

		~CurveInterpolator() = default;

		double interpol(const double& queryTime, const map<double, double>& data) const override;

	private:
		function<double(const double&, const map<double, double>&)> leftExtrapolFunc_;
		function<double(const double&, const map<double, double>&)> interpolFunc_;
		function<double(const double&, const map<double, double>&)> rightExtrapolFunc_;
	};
}