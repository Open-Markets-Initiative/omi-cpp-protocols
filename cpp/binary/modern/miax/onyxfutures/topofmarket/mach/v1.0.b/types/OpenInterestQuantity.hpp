#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

// The amount of aggregate open contracts in a Simple Instrument
struct OpenInterestQuantity {

    static constexpr const char* name = "Open Interest Quantity";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr OpenInterestQuantity()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OpenInterestQuantity(const std::uint32_t value)
     : value{ value } {}

    // get value of OpenInterestQuantity field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
