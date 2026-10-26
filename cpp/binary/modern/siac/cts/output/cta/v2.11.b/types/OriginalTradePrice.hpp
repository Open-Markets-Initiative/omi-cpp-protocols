#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v2_11_b {

// Original monetary value of an individual share of security. Has implied 6 decimal places
struct OriginalTradePrice {

    static constexpr const char* name = "Original Trade Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 6;
    static constexpr double denominator = 1000000;
    using type = std::uint64_t;

    // default constructor
    constexpr OriginalTradePrice()
     : value{ 0 } {}

    // constructor for OriginalTradePrice field
    constexpr explicit OriginalTradePrice(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of OriginalTradePrice field
    [[nodiscard]] std::uint64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of OriginalTradePrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
