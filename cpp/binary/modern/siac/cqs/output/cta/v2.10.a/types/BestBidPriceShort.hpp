#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cqs::output::cta::v2_10_a {

// Represents the Best Bid Price on a consolidated basis. Has implied 2 decimal places
struct BestBidPriceShort {

    static constexpr const char* name = "Best Bid Price Short";
    static constexpr std::size_t size =  2;
    static constexpr std::size_t precision = 2;
    static constexpr double denominator = 100;
    using type = std::uint16_t;

    // default constructor
    constexpr BestBidPriceShort()
     : value{ 0 } {}

    // constructor for BestBidPriceShort field
    constexpr explicit BestBidPriceShort(const std::uint16_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of BestBidPriceShort field
    [[nodiscard]] std::uint16_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of BestBidPriceShort field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint16_t value;
};
}
