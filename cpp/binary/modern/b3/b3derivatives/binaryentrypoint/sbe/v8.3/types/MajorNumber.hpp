#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {


// majorNumber
struct MajorNumber {

    static constexpr auto name = "Major Number";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr MajorNumber()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MajorNumber(const std::uint8_t &value)
     : value{ value } {}

    // get value of MajorNumber field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
