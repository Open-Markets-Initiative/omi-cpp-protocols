#pragma once

#include <cstddef>

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {


// Customer or Firm capacity specified with the order. Values include:
struct Capacity {

    static constexpr auto name = "Capacity";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr Capacity()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Capacity(const char &value)
     : value{ value } {}

    // get value of Capacity field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
