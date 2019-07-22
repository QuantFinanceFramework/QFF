#pragma once
#include <memory>
#include <vector>
#include "BaseCalendar.h"

namespace qff {
using std::unique_ptr;
using std::vector;

class CompositeCalendar : public BaseCalendar {
 public:
  CompositeCalendar(vector<unique_ptr<ICalendar>> calendarList);

  template <typename... Ts>
  CompositeCalendar(Ts&&... calendars) : calendarList_(sizeof...(calendars)) {
    unique_ptr<ICalendar> calendarArr[] = {
        std::make_unique<Ts>(std::move(calendars))...};
    calendarList_ = vector<unique_ptr<ICalendar>>{
        std::make_move_iterator(std::begin(calendarArr)),
        std::make_move_iterator(std::end(calendarArr))};
  };

  unique_ptr<ICalendar> clone() override;

  bool isHoliday(const date& queryDate) const override;

 private:
  vector<unique_ptr<ICalendar>> calendarList_;
};
}  // namespace qff