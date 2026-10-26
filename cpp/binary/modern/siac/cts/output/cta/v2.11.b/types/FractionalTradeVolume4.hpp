#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v2_11_b {

// Contains the total number of shares which traded in a single transaction for an individual security. Has implied 6 decimal places
struct FractionalTradeVolume4 {

    static constexpr const char* name = "Fractional Trade Volume 4";
    static constexpr std::size_t size =  4;
    static constexpr std::size_t precision = 6;
    static constexpr double denominator = 1000000;
    using type = std::uint32_t;

    // default constructor
    constexpr FractionalTradeVolume4()
     : value{ 0 } {}

    // constructor for FractionalTradeVolume4 field
    constexpr explicit FractionalTradeVolume4(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of FractionalTradeVolume4 field
    [[nodiscard]] std::uint32_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of FractionalTradeVolume4 field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint32_t value;
};
}
