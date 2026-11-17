// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/TradeId.hpp
#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace otcmarkets::linkats::multicast::link::v4_3 {

// Unique Trade ID.
struct TradeId {

    static constexpr const char* name = "Trade Id";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr TradeId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TradeId(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of TradeId field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
