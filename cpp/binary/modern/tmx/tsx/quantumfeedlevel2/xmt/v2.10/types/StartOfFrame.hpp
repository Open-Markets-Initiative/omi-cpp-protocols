#pragma once

#include <cstddef>
#include <cstdint>

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {


// Start of Frame
struct StartOfFrame {

    static constexpr auto name = "Start Of Frame";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;
static const type static_value = 2;

    // default constructor
    constexpr StartOfFrame()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit StartOfFrame(const std::uint8_t &value)
     : value{ value } {}

    // get value of StartOfFrame field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
