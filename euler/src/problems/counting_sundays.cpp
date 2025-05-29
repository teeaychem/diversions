#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>
void counting_sundays() {
  std::vector<int64_t> month_days{31, 28, 31, 30, 31, 30,
                                  31, 31, 30, 31, 30, 31};

  int64_t day{1};
  size_t first_sundays{0};
  bool leap{false};

  auto leap_year = [](size_t year) {
    return (year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0));
  };

  for (size_t i{0}; i < 12; ++i) {
    day += month_days.at(i);
  }

  for (size_t year{1901}; year < 2001; ++year) {
    if (leap) {
      day -= 365;
      month_days.at(1) = 28;
    } else {
      day -= 364;
    }

    leap = leap_year(year);

    if (leap) {
      month_days.at(1) = 29;
    }

    for (size_t i{0}; i < 12; ++i) {
      if (day % 7 == 0) {
        first_sundays++;
      }

      day += month_days.at(i);
    }
  }

  std::cout << first_sundays << "\n";
}
