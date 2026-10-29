#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::byxequities::multicastdepthofbook::pitch::v2_41_29 {


// Unit that applies to messages included in this header
struct Unit {

    static constexpr auto name = "Unit";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr Unit()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Unit(const std::uint8_t &value)
     : value{ value } {}

    // get value of Unit field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
