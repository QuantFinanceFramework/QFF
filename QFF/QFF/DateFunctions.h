#pragma once
#include <boost/date_time/gregorian/gregorian.hpp>
#include "IDayCounter.h"

namespace qff {
using boost::gregorian::date;

double DateToTime(const IDayCounter& day_counter, const date& start_date, const date& end_date);

}