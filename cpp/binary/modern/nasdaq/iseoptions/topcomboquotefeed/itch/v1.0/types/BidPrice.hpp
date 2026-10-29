#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

// Best bid price in fixed point format with 6 whole number places followed by 4 decimal digits.
struct BidPrice {

    static constexpr const char* name = "Bid Price";
    static constexpr std::size_t size =  4;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::int32_t;

    // default constructor
    constexpr BidPrice()
     : value{ 0 } {}

    // constructor for BidPrice field
    constexpr explicit BidPrice(const std::int32_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of BidPrice field
    [[nodiscard]] std::int32_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of BidPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int32_t value;
};
}
