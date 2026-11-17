// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/AskPrice.hpp
#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace otcmarkets::linkats::multicast::link::v4_3 {

// Ask price, with 6 decimal places assumed.
struct AskPrice {

    static constexpr const char* name = "Ask Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 6;
    static constexpr double denominator = 1000000;
    using type = std::uint64_t;

    // default constructor
    constexpr AskPrice()
     : value{ 0 } {}

    // constructor for AskPrice field
    constexpr explicit AskPrice(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of AskPrice field
    [[nodiscard]] std::uint64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of AskPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
