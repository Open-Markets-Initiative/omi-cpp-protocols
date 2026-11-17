// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/MarketOpen.hpp
#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace otcmarkets::linkats::multicast::link::v4_3 {

// Market open time in milliseconds since UTC epoch.
struct MarketOpen {

    static constexpr const char* name = "Market Open";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr MarketOpen()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MarketOpen(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of MarketOpen field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
