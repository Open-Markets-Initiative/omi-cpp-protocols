#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {


// Reserved. Value will always be zero.
struct Reserved1 {

    static constexpr auto name = "Reserved 1";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr Reserved1()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Reserved1(const std::uint8_t &value)
     : value{ value } {}

    // get value of Reserved1 field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
