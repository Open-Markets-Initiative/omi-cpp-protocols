#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v2_11_b {

// Consolidated highest price paid during the trading day. Has implied 6 decimal places
struct ConsolidatedHighPrice {

    static constexpr const char* name = "Consolidated High Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 6;
    static constexpr double denominator = 1000000;
    using type = std::uint64_t;

    // default constructor
    constexpr ConsolidatedHighPrice()
     : value{ 0 } {}

    // constructor for ConsolidatedHighPrice field
    constexpr explicit ConsolidatedHighPrice(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of ConsolidatedHighPrice field
    [[nodiscard]] std::uint64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of ConsolidatedHighPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
