#include <ICashflow.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;
using namespace pybind11::literals;

void init_i_cashflow(py::module &m) {
  py::class_<qff_a::ICashflow>(m, "ICashflow");
}