#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {


// day
struct Day {

    static constexpr auto name = "Day";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr Day()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Day(const std::uint8_t &value)
     : value{ value } {}

    // get value of Day field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
