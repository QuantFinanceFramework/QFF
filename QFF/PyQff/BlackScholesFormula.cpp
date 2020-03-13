#include <BlackScholesFormula.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;
using namespace pybind11::literals;

void init_black_scholes_formula(py::module &m) {
  m.def("black_scholes_formula", &qff_a::BlackScholesFormula<double>,
        R"pbdoc(Black Scholes formula for European option pricing)pbdoc",
        "spot"_a, "strike"_a, "discount_factor"_a, "time_to_maturity"_a,
        "volatility"_a, "option_type"_a);
}
