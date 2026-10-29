#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::c1options::complex::pitch::v2_1_18 {


// The number of legs in the complex instrument. The maximum number of legs is 12.
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
