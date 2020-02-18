#include <Actual360.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;
using namespace pybind11::literals;

void init_actual_360(py::module &m) {
  py::class_<qff::Actual360>(m, "Actual360")
      .def(py::init<>())
      .def("CalculateYearFraction", &qff::Actual360::CalculateYearFraction,
           "start_date"_a, "end_date"_a, "is_maturity"_a = false);
}