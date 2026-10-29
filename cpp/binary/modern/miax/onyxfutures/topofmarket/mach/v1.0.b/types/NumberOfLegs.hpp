#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {


// Number of strategy legs
struct NumberOfLegs {

    static constexpr auto name = "Number Of Legs";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr NumberOfLegs()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit NumberOfLegs(const std::uint8_t &value)
     : value{ value } {}

    // get value of NumberOfLegs field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
