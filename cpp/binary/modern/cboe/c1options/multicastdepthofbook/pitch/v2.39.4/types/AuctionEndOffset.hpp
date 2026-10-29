#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4 {

// Nanosecond offset from last timestamp
struct AuctionEndOffset {

    static constexpr const char* name = "Auction End Offset";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr AuctionEndOffset()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit AuctionEndOffset(const std::uint32_t value)
     : value{ value } {}

    // get value of AuctionEndOffset field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
