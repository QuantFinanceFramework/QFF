#include <Black76Formula.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;
using namespace pybind11::literals;

void init_black_76_formula(py::module &m) {
  m.def("black_76_formula", &qff::Black76Formula,
        R"pbdoc(Black 76 formula for European option pricing)pbdoc",
        "forward"_a, "strike"_a, "discount_factor"_a, "time_to_maturity"_a,
        "volatility"_a, "option_type"_a);
}