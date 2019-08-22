#pragma once
#include <boost/date_time/gregorian/gregorian.hpp>
#include "IDayCounter.h"

namespace qff {
double DateToTime(const IDayCounter& day_counter,
                  const boost::gregorian::date& start_date,
                  const boost::gregorian::date& end_date);

}