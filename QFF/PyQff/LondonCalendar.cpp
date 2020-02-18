#include <LondonCalendar.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;
using namespace pybind11::literals;

void init_london_calendar(py::module &m) {
  py::class_<qff::LondonCalendar, qff::ICalendar>(m, "LondonCalendar")
      .def(py::init<>())
      .def("IsHoliday", &qff::LondonCalendar::IsHoliday, "query_date"_a)
      .def("IsBusinessDay", &qff::LondonCalendar::IsBusinessDay, "query_date"_a)
      .def("IsWeekend", &qff::LondonCalendar::IsWeekend, "query_date"_a);
}