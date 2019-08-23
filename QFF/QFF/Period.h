#pragma once

namespace qff {

enum class TimeUnit { d, w, m, y, b };

struct Period {
  Period() = default;
  Period(int length, TimeUnit unit);
  ~Period() = default;

  Period& operator+=(const Period& rhs);
  Period& operator-=(const Period& rhs);
  Period& operator-();

  int length;
  TimeUnit unit;
};

Period operator+(const Period& lhs, const Period& rhs);

Period operator-(const Period& lhs, const Period& rhs);

Period operator-(const Period& rhs);

}  // namespace qff