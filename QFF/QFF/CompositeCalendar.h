#pragma once
#include <memory>
#include <vector>
#include "BaseCalendar.h"

namespace qff {
using std::unique_ptr;
using std::vector;

class CompositeCalendar : public BaseCalendar {
 public:
  CompositeCalendar(vector<unique_ptr<ICalendar>> calendar_list);

  template <typename... Ts>
  CompositeCalendar(Ts&&... calendars) : calendar_list_(sizeof...(calendars)) {
    unique_ptr<ICalendar> calendar_arr[] = {
        std::make_unique<Ts>(std::move(calendars))...};
    calendar_list_ = vector<unique_ptr<ICalendar>>{
        std::make_move_iterator(std::begin(calendar_arr)),
        std::make_move_iterator(std::end(calendar_arr))};
  };

  unique_ptr<ICalendar> Clone() const override;

  bool IsHoliday(const date& query_date) const override;

 private:
  vector<unique_ptr<ICalendar>> calendar_list_;
};
}  // namespace qff