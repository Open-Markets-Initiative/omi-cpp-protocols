#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace asx::asxderivatives::ntp::itch::v1_05 {

// Minimum tick size for the Strike Price. Divide by the Strike Price Fractional Denominator to determine the floating point value.
struct StrikePriceMinimumTick {

    static constexpr const char* name = "Strike Price Minimum Tick";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr StrikePriceMinimumTick()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit StrikePriceMinimumTick(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of StrikePriceMinimumTick field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
