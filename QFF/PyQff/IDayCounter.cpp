#include <IDayCounter.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;
using namespace pybind11::literals;

void init_i_day_counter(py::module &m) {
  py::class_<qff::IDayCounter>(m, "IDayCounter")
      .def("CalculateYearFraction", &qff::IDayCounter::CalculateYearFraction,
           "start_date"_a, "end_date"_a, "is_maturity"_a = false);
}