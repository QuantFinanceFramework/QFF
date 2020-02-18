#include <IDayCounter.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;

void init_i_day_counter(py::module &m) {
  py::class_<qff::IDayCounter>(m, "IDayCounter");
}