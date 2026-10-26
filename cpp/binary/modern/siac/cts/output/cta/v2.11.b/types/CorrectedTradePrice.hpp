#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v2_11_b {

// Corrected monetary value of an individual share of security. Has implied 6 decimal places
struct CorrectedTradePrice {

    static constexpr const char* name = "Corrected Trade Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 6;
    static constexpr double denominator = 1000000;
    using type = std::uint64_t;

    // default constructor
    constexpr CorrectedTradePrice()
     : value{ 0 } {}

    // constructor for CorrectedTradePrice field
    constexpr explicit CorrectedTradePrice(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of CorrectedTradePrice field
    [[nodiscard]] std::uint64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of CorrectedTradePrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
