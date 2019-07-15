#pragma once
#include <map>
using std::map;

double linearInterpol(const double & query, const map<double, double> & data);

double logLinearInterpol(const double& query, const map<double, double>& data);