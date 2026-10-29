#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

// The consolidated low price for the issue for the trading day
struct ConsolidatedLowPriceLong {

    static constexpr const char* name = "Consolidated Low Price Long";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::uint64_t;

    // default constructor
    constexpr ConsolidatedLowPriceLong()
     : value{ 0 } {}

    // constructor for ConsolidatedLowPriceLong field
    constexpr explicit ConsolidatedLowPriceLong(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of ConsolidatedLowPriceLong field
    [[nodiscard]] std::uint64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of ConsolidatedLowPriceLong field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
