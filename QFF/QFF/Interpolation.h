#pragma once
#include <map>

namespace qff {
using std::map;

double LinearInterpol(const double& query, const map<double, double>& data);

double LogLinearInterpol(const double& query, const map<double, double>& data);

double LinearExtrapol(const double& query, const map<double, double>& data);

double LogLinearExtrapol(const double& query, const map<double, double>& data);

double ConstantExtrapol(const double& query, const map<double, double>& data);

}  // namespace qff