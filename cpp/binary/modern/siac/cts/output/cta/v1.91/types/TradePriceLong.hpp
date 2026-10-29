#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v1_91 {

// The Trade Price is the monetary value of an individual share of security at the time of the trade
struct TradePriceLong {

    static constexpr const char* name = "Trade Price Long";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 6;
    static constexpr double denominator = 1000000;
    using type = std::uint64_t;

    // default constructor
    constexpr TradePriceLong()
     : value{ 0 } {}

    // constructor for TradePriceLong field
    constexpr explicit TradePriceLong(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of TradePriceLong field
    [[nodiscard]] std::uint64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of TradePriceLong field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
