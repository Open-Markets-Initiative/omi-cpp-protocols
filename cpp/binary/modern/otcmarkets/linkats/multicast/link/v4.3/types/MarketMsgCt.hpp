// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/MarketMsgCt.hpp
#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace otcmarkets::linkats::multicast::link::v4_3 {

// Total message count for the trading day.
struct MarketMsgCt {

    static constexpr const char* name = "Market Msg Ct";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr MarketMsgCt()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MarketMsgCt(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of MarketMsgCt field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
