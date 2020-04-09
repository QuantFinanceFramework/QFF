#include "ImmDates.h"

#include <boost/date_time/date_generators.hpp>

namespace qff_a {
using namespace boost::date_time;
using boost::gregorian::date;

date NextImmDate(const date& original_date) {
  const nth_kday_of_month<date> first_imm(nth_kday_of_month<date>::third,
                                          Wednesday, Mar);
  const nth_kday_of_month<date> second_imm(nth_kday_of_month<date>::third,
                                           Wednesday, Jun);
  const nth_kday_of_month<date> third_imm(nth_kday_of_month<date>::third,
                                          Wednesday, Sep);
  const nth_kday_of_month<date> fourth_imm(nth_kday_of_month<date>::third,
                                           Wednesday, Dec);
  const auto year = original_date.year();
  const auto first_imm_date = first_imm.get_date(year);
  const auto second_imm_date = second_imm.get_date(year);
  const auto third_imm_date = third_imm.get_date(year);
  const auto fourth_imm_date = fourth_imm.get_date(year);
  const auto next_first_imm_date = first_imm.get_date(year + 1);

  if (original_date < first_imm_date) {
    return first_imm_date;
  }
  if (original_date < second_imm_date) {
    return second_imm_date;
  }
  if (original_date < third_imm_date) {
    return third_imm_date;
  }
  if (original_date < fourth_imm_date) {
    return fourth_imm_date;
  }
  return next_first_imm_date;
}
}  // namespace qff_a
