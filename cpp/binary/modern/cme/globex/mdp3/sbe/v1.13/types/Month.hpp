#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {


// MM
struct Month {

    static constexpr auto name = "Month";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;
static const type no_value = 255;

    // default constructor
    constexpr Month()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Month(const std::uint8_t &value)
     : value{ value } {}

    // get value of Month field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
