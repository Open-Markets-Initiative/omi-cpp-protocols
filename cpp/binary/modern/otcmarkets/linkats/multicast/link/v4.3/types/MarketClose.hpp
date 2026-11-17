// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/MarketClose.hpp
#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace otcmarkets::linkats::multicast::link::v4_3 {

// Anticipated market close time in milliseconds since UTC epoch.
struct MarketClose {

    static constexpr const char* name = "Market Close";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr MarketClose()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MarketClose(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of MarketClose field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
