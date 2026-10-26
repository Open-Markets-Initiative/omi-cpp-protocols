#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

// Best bid price, or zero if the book is crossed
struct BestBidPrice {

    static constexpr const char* name = "Best Bid Price";
    static constexpr std::size_t size =  4;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::uint32_t;

    // default constructor
    constexpr BestBidPrice()
     : value{ 0 } {}

    // constructor for BestBidPrice field
    constexpr explicit BestBidPrice(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of BestBidPrice field
    [[nodiscard]] std::uint32_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of BestBidPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint32_t value;
};
}
