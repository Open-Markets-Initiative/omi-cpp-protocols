#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {


// The current calendar month, with values 1 to 12 inclusive, January=1, etc.
struct CurrentMonth {

    static constexpr auto name = "Current Month";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr CurrentMonth()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CurrentMonth(const std::uint8_t &value)
     : value{ value } {}

    // get value of CurrentMonth field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
