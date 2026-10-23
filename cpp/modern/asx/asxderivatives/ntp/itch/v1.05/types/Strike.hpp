#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace asx::asxderivatives::ntp::itch::v1_05 {

// Strike price of contract. Divide by the Strike Price Fractional Denominator to determine the floating point value.
struct Strike {

    static constexpr const char* name = "Strike";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 2;
    static constexpr double denominator = 100;
    using type = std::int64_t;

    // default constructor
    constexpr Strike()
     : value{ 0 } {}

    // constructor for Strike field
    constexpr explicit Strike(const std::int64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of Strike field
    [[nodiscard]] std::int64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of Strike field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
