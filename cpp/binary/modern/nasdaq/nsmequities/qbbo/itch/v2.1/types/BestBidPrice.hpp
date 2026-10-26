#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

// Denotes the best bid price, or the highest price for market buy order(s) in the execution system.
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
