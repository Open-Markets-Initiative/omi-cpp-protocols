#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {


// Values greater than 0 indicate this is a spread instrument.
struct LegCount {

    static constexpr auto name = "Leg Count";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr LegCount()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LegCount(const std::uint8_t &value)
     : value{ value } {}

    // get value of LegCount field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
