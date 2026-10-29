#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4 {


// Current Pitch message length
struct MessageLength {

    static constexpr auto name = "Message Length";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr MessageLength()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MessageLength(const std::uint8_t &value)
     : value{ value } {}

    // get value of MessageLength field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
