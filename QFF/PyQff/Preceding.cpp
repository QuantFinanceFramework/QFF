#include <Preceding.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;
using namespace pybind11::literals;

void init_preceding(py::module &m) {
  py::class_<qff::Preceding, qff::IBusinessDayConvention>(m, "Preceding")
      .def(py::init<>())
      .def("Adjust", &qff::Preceding::Adjust, "original_date"_a, "calendar"_a);
}