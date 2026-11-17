// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/TradePrice.hpp
#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace otcmarkets::linkats::multicast::link::v4_3 {

// Trade price with 6 decimal places assumed.
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
