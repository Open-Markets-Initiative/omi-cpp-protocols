#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v2_11_b {

// Represents the monetary value of an individual share of security at the time of the trade. Has implied 2 decimal places
struct TradePrice2 {

    static constexpr const char* name = "Trade Price 2";
    static constexpr std::size_t size =  2;
    static constexpr std::size_t precision = 2;
    static constexpr double denominator = 100;
    using type = std::uint16_t;

    // default constructor
    constexpr TradePrice2()
     : value{ 0 } {}

    // constructor for TradePrice2 field
    constexpr explicit TradePrice2(const std::uint16_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of TradePrice2 field
    [[nodiscard]] std::uint16_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of TradePrice2 field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint16_t value;
};
}
