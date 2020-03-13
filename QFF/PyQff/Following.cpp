#include <Following.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;

void init_following(py::module &m) {
  py::class_<qff_a::Following, qff_a::IBusinessDayConvention>(m, "Following")
      .def(py::init<>());
}