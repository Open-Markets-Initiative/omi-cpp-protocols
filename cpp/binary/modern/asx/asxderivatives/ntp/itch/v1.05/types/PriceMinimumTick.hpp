#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace asx::asxderivatives::ntp::itch::v1_05 {

// Minimum tick size. Divide by the Price Fractional Denominator to determine the floating point value.
struct PriceMinimumTick {

    static constexpr const char* name = "Price Minimum Tick";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr PriceMinimumTick()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PriceMinimumTick(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of PriceMinimumTick field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
