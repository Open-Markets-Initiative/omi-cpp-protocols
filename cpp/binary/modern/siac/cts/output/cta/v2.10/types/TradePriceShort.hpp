#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v2_10 {

// The Trade Price is the monetary value of an individual share of security at the time of the trade
struct TradePriceShort {

    static constexpr const char* name = "Trade Price Short";
    static constexpr std::size_t size =  2;
    static constexpr std::size_t precision = 2;
    static constexpr double denominator = 100;
    using type = std::uint16_t;

    // default constructor
    constexpr TradePriceShort()
     : value{ 0 } {}

    // constructor for TradePriceShort field
    constexpr explicit TradePriceShort(const std::uint16_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of TradePriceShort field
    [[nodiscard]] std::uint16_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of TradePriceShort field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint16_t value;
};
}
