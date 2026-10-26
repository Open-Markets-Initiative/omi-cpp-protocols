#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cqs::output::cta::v2_10_a {

// Represents the Best Bid Size associated with the Best Bid Price on a consolidated basis
struct BestBidSizeLong {

    static constexpr const char* name = "Best Bid Size Long";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr BestBidSizeLong()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BestBidSizeLong(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of BestBidSizeLong field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
