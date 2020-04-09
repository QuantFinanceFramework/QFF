#pragma once
#include <boost/date_time/gregorian/gregorian.hpp>

namespace qff_a {
// International Monetary Market (IMM) dates are the third Wednesday of March,
// June, September and December
boost::gregorian::date NextImmDate(const boost::gregorian::date& original_date);
}  // namespace qff_a
