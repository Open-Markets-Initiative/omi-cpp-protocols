// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/MarketCloseTimeMilli.hpp
#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace otcmarkets::linkats::multicast::link::v4_3 {

// Market close time in milliseconds since UTC epoch midnight.
struct MarketCloseTimeMilli {

    static constexpr const char* name = "Market Close Time Milli";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr MarketCloseTimeMilli()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MarketCloseTimeMilli(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of MarketCloseTimeMilli field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
