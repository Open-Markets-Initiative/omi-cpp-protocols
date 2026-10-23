#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cqs::output::cta::v2_10_a {

// Represents the Best Bid Size associated with the Best Bid Price on a consolidated basis
struct BestBidSizeShort {

    static constexpr const char* name = "Best Bid Size Short";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr BestBidSizeShort()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BestBidSizeShort(const std::uint16_t value)
     : value{ std::byteswap(value) } {}

    // get value of BestBidSizeShort field
    [[nodiscard]] std::uint16_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint16_t value;
};
}
