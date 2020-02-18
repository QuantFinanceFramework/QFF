#include <IBusinessDayConvention.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;

void init_i_business_day_convention(py::module &m) {
  py::class_<qff::IBusinessDayConvention>(m, "IBusinessDayConvention");
}