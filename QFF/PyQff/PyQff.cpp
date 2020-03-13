#include <pybind11/pybind11.h>
namespace py = pybind11;

void init_black_scholes_formula(py::module &);
void init_black_76_formula(py::module &);

void init_boost_date(py::module &);
void init_boost_date_from_string(py::module &);
void init_boost_date_to_string(py::module &);

void init_i_day_counter(py::module &);
void init_actual_360(py::module &);
void init_actual_365(py::module &);
void init_thirty_360_isda(py::module &);

void init_i_calendar(py::module &);
void init_sydney_calendar(py::module &);
void init_new_york_fed_calendar(py::module &);
void init_london_calendar(py::module &);

void init_i_business_day_convention(py::module &);
void init_following(py::module &);
void init_modified_following(py::module &);
void init_preceding(py::module &);
void init_unadjusted(py::module &);

void init_i_interest_rate_curve(py::module &);
void init_interest_rate_curve(py::module &);
void init_flat_zero_rate_curve(py::module &);

void init_i_credit_curve(py::module &);

PYBIND11_MODULE(pyqff, m) {
  init_black_scholes_formula(m);
  init_black_76_formula(m);

  init_boost_date(m);
  init_boost_date_from_string(m);
  init_boost_date_to_string(m);

  init_i_day_counter(m);
  init_actual_360(m);
  init_actual_365(m);
  init_thirty_360_isda(m);

  init_i_calendar(m);
  init_sydney_calendar(m);
  init_new_york_fed_calendar(m);
  init_london_calendar(m);

  init_i_business_day_convention(m);
  init_following(m);
  init_modified_following(m);
  init_preceding(m);
  init_unadjusted(m);

  init_i_interest_rate_curve(m);
  init_interest_rate_curve(m);
  init_flat_zero_rate_curve(m);

  init_i_credit_curve(m);
}
