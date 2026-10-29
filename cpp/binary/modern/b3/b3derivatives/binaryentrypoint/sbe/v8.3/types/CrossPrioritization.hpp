#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {


// crossPrioritization
struct CrossPrioritization {

    static constexpr auto name = "Cross Prioritization";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;
static const type no_value = 255;

    // default constructor
    constexpr CrossPrioritization()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CrossPrioritization(const std::uint8_t &value)
     : value{ value } {}

    // get value of CrossPrioritization field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
