#include <pybind11/pybind11.h>
namespace py = pybind11;

void init_black_scholes_formula(py::module &);
void init_black_76_formula(py::module &);
void init_actual_360(py::module &);
void init_boost_date(py::module &);
void init_boost_date_from_string(py::module &);

PYBIND11_MODULE(pyqff, m) {
  init_black_scholes_formula(m);
  init_black_76_formula(m);
  init_actual_360(m);
  init_boost_date(m);
  init_boost_date_from_string(m);
}
