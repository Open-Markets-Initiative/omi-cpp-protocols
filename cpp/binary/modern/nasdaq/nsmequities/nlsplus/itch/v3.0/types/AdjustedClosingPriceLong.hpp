#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

// Denotes the adjusted previous close price for the issue
struct AdjustedClosingPriceLong {

    static constexpr const char* name = "Adjusted Closing Price Long";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::uint64_t;

    // default constructor
    constexpr AdjustedClosingPriceLong()
     : value{ 0 } {}

    // constructor for AdjustedClosingPriceLong field
    constexpr explicit AdjustedClosingPriceLong(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of AdjustedClosingPriceLong field
    [[nodiscard]] std::uint64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of AdjustedClosingPriceLong field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
