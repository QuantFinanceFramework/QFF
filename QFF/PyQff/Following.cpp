#include <Following.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;

void init_following(py::module &m) {
  py::class_<qff::Following, qff::IBusinessDayConvention>(m, "Following")
      .def(py::init<>());
}