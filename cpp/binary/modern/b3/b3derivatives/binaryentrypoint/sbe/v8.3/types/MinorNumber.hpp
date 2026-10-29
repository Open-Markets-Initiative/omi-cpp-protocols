#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {


// minorNumber
struct MinorNumber {

    static constexpr auto name = "Minor Number";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr MinorNumber()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MinorNumber(const std::uint8_t &value)
     : value{ value } {}

    // get value of MinorNumber field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
