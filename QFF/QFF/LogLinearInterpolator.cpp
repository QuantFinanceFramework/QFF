#include "LogLinearInterpolator.h"
#include <cmath>

double logLinearInterpol(const double & query, const map<double, double>& data)
{
	auto position = data.find(query);
	if (position == data.end()) {
		auto next = data.upper_bound(query);
		auto previous = std::prev(next);
		if (next == data.end())
		{
			return previous->second;
		}
		if (next == data.begin())
		{
			return next->second;
		}

		auto delta = (query - previous->first) / (next->first - previous->first);
		return exp(delta * log(next->second) + (1 - delta) * log(previous->second));
	}
	else {
		return position->second;
	}
}
