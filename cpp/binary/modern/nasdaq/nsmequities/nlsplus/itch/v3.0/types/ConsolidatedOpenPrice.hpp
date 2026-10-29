#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

// The consolidated opening price for the issue for the trading day
struct ConsolidatedOpenPrice {

    static constexpr const char* name = "Consolidated Open Price";
    static constexpr std::size_t size =  4;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::uint32_t;

    // default constructor
    constexpr ConsolidatedOpenPrice()
     : value{ 0 } {}

    // constructor for ConsolidatedOpenPrice field
    constexpr explicit ConsolidatedOpenPrice(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of ConsolidatedOpenPrice field
    [[nodiscard]] std::uint32_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of ConsolidatedOpenPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint32_t value;
};
}
