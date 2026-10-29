#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {


// The current calendar day, with values 1 to 31 inclusive.
struct CurrentDay {

    static constexpr auto name = "Current Day";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr CurrentDay()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CurrentDay(const std::uint8_t &value)
     : value{ value } {}

    // get value of CurrentDay field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
