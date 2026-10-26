#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

// The price at which the order execution occurred
struct TradePrice {

    static constexpr const char* name = "Trade Price";
    static constexpr std::size_t size =  4;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::uint32_t;

    // default constructor
    constexpr TradePrice()
     : value{ 0 } {}

    // constructor for TradePrice field
    constexpr explicit TradePrice(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of TradePrice field
    [[nodiscard]] std::uint32_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of TradePrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint32_t value;
};
}
