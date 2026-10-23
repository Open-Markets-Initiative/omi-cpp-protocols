#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::opra::output::obi::v6_2 {

// The Bid Size identifies the number of contracts being bought for an option at the Bid Price.
struct BidSizeShort {

    static constexpr const char* name = "Bid Size Short";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr BidSizeShort()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BidSizeShort(const std::uint16_t value)
     : value{ std::byteswap(value) } {}

    // get value of BidSizeShort field
    [[nodiscard]] std::uint16_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint16_t value;
};
}
