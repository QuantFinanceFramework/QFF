#include <Thirty360Isda.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;
using namespace pybind11::literals;

void init_thirty_360_isda(py::module &m) {
  py::class_<qff::Thirty360Isda, qff::IDayCounter>(m, "Thirty360Isda")
      .def(py::init<>())
      .def("CalculateYearFraction", &qff::Thirty360Isda::CalculateYearFraction,
           "start_date"_a, "end_date"_a, "is_maturity"_a = false);
}