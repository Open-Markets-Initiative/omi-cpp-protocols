// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/BidSize.hpp
#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace otcmarkets::linkats::multicast::link::v4_3 {

// Number of shares on the bid.
struct BidSize {

    static constexpr const char* name = "Bid Size";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr BidSize()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BidSize(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of BidSize field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
