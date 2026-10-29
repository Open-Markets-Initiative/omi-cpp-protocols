#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

// Denotes the adjusted previous close price for the issue
struct AdjustedClosingPrice {

    static constexpr const char* name = "Adjusted Closing Price";
    static constexpr std::size_t size =  4;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::uint32_t;

    // default constructor
    constexpr AdjustedClosingPrice()
     : value{ 0 } {}

    // constructor for AdjustedClosingPrice field
    constexpr explicit AdjustedClosingPrice(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of AdjustedClosingPrice field
    [[nodiscard]] std::uint32_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of AdjustedClosingPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint32_t value;
};
}
