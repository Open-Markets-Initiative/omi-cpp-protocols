#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

// The consolidated high price for the issue for the trading day
struct ConsolidatedHighPrice {

    static constexpr const char* name = "Consolidated High Price";
    static constexpr std::size_t size =  4;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::uint32_t;

    // default constructor
    constexpr ConsolidatedHighPrice()
     : value{ 0 } {}

    // constructor for ConsolidatedHighPrice field
    constexpr explicit ConsolidatedHighPrice(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of ConsolidatedHighPrice field
    [[nodiscard]] std::uint32_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of ConsolidatedHighPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint32_t value;
};
}
