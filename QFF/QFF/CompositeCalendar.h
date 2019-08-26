#pragma once
#include <memory>
#include <vector>
#include "BaseCalendar.h"

namespace qff {
class CompositeCalendar : public BaseCalendar {
 public:
  CompositeCalendar(std::vector<std::unique_ptr<ICalendar>> calendar_list);

  template <typename... Ts>
  CompositeCalendar(Ts&&... calendars) : calendar_list_(sizeof...(calendars)) {
    std::unique_ptr<ICalendar> calendar_arr[] = {
        std::make_unique<Ts>(std::move(calendars))...};
    calendar_list_ = std::vector<std::unique_ptr<ICalendar>>{
        std::make_move_iterator(std::begin(calendar_arr)),
        std::make_move_iterator(std::end(calendar_arr))};
  };

  std::unique_ptr<ICalendar> Clone() const override;

  bool IsHoliday(const boost::gregorian::date& query_date) const override;

 private:
  std::vector<std::unique_ptr<ICalendar>> calendar_list_;
};
}  // namespace qff