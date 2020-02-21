#include <ICreditCurve.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;
using namespace pybind11::literals;

void init_i_credit_curve(py::module &m) {
  py::class_<qff::ICreditCurve>(m, "ICreditCurve");
}