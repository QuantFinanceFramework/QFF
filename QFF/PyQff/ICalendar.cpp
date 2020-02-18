#include <ICalendar.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;

void init_i_calendar(py::module &m) {
  py::class_<qff::ICalendar>(m, "ICalendar");
}