// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/BidTimeMilli.hpp
#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace otcmarkets::linkats::multicast::link::v4_3 {

// Bid timestamp in milliseconds from UTC epoch.
struct BidTimeMilli {

    static constexpr const char* name = "Bid Time Milli";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr BidTimeMilli()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BidTimeMilli(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of BidTimeMilli field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
