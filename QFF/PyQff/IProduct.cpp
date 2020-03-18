#include <IProduct.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;
using namespace pybind11::literals;

void init_i_product(py::module &m) {
  py::class_<qff_a::IProduct>(m, "IProduct");
}