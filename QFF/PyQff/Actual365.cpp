#include <Actual365.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;
using namespace pybind11::literals;

void init_actual_365(py::module &m) {
  py::class_<qff::Actual365>(m, "Actual365")
      .def(py::init<>())
      .def("CalculateYearFraction", &qff::Actual365::CalculateYearFraction,
           "start_date"_a, "end_date"_a, "is_maturity"_a = false);
}