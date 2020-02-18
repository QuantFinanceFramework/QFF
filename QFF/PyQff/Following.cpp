#include <Following.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;
using namespace pybind11::literals;

void init_following(py::module &m) {
  py::class_<qff::Following, qff::IBusinessDayConvention>(m, "Following")
      .def(py::init<>())
      .def("Adjust", &qff::Following::Adjust, "original_date"_a, "calendar"_a);
}