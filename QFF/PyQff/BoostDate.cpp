#include <pybind11/pybind11.h>
#include "boost/date_time/gregorian/gregorian.hpp"

namespace py = pybind11;
using namespace pybind11::literals;

void init_boost_date(py::module &m) {
  py::class_<boost::gregorian::date>(m, "BoostDate")
      .def("day_of_year", &boost::gregorian::date::day_of_year);
}

void init_boost_date_from_string(py::module &m) {
  m.def("as_boost_date", &boost::gregorian::from_string);
}