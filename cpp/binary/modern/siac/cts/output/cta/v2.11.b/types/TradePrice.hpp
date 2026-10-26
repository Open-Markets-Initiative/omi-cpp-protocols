#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v2_11_b {

// Represents the monetary value of an individual share of security at the time of the trade. Has implied 6 decimal places
struct TradePrice {

    static constexpr const char* name = "Trade Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 6;
    static constexpr double denominator = 1000000;
    using type = std::uint64_t;

    // default constructor
    constexpr TradePrice()
     : value{ 0 } {}

    // constructor for TradePrice field
    constexpr explicit TradePrice(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of TradePrice field
    [[nodiscard]] std::uint64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of TradePrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
