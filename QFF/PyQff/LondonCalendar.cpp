#include <LondonCalendar.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;
using namespace pybind11::literals;

void init_london_calendar(py::module &m) {
  py::class_<qff::LondonCalendar, qff::ICalendar>(m, "LondonCalendar")
      .def(py::init<>());
}