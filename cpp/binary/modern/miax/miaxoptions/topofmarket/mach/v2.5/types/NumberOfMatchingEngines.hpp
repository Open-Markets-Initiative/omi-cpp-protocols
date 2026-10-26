#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::miaxoptions::topofmarket::mach::v2_5 {


// Count of all Matching Engines for the exchange
struct NumberOfMatchingEngines {

    static constexpr auto name = "Number Of Matching Engines";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr NumberOfMatchingEngines()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit NumberOfMatchingEngines(const std::uint8_t &value)
     : value{ value } {}

    // get value of NumberOfMatchingEngines field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
