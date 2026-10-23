#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v2_11_b {

// Consolidated total volume of shares traded. Has implied 6 decimal places
struct ConsolidatedFractionalTotalVolume {

    static constexpr const char* name = "Consolidated Fractional Total Volume";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr ConsolidatedFractionalTotalVolume()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ConsolidatedFractionalTotalVolume(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of ConsolidatedFractionalTotalVolume field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
