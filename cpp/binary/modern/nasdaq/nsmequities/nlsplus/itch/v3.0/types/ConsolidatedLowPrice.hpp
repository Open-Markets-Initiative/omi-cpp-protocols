#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

// The consolidated low price for the issue for the trading day
struct ConsolidatedLowPrice {

    static constexpr const char* name = "Consolidated Low Price";
    static constexpr std::size_t size =  4;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::uint32_t;

    // default constructor
    constexpr ConsolidatedLowPrice()
     : value{ 0 } {}

    // constructor for ConsolidatedLowPrice field
    constexpr explicit ConsolidatedLowPrice(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of ConsolidatedLowPrice field
    [[nodiscard]] std::uint32_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of ConsolidatedLowPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint32_t value;
};
}
