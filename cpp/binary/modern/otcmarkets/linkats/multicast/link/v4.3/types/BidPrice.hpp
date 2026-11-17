// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/BidPrice.hpp
#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace otcmarkets::linkats::multicast::link::v4_3 {

// Bid price, with 6 decimal places assumed.
struct BidPrice {

    static constexpr const char* name = "Bid Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 6;
    static constexpr double denominator = 1000000;
    using type = std::uint64_t;

    // default constructor
    constexpr BidPrice()
     : value{ 0 } {}

    // constructor for BidPrice field
    constexpr explicit BidPrice(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of BidPrice field
    [[nodiscard]] std::uint64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of BidPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
