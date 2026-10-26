#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {


// Leg definitions, if any, begin at this offset from the beginning of the message. Possible values are 0 (no legs present) or 45 (spread instrument).
struct LegOffset {

    static constexpr auto name = "Leg Offset";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr LegOffset()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LegOffset(const std::uint8_t &value)
     : value{ value } {}

    // get value of LegOffset field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
