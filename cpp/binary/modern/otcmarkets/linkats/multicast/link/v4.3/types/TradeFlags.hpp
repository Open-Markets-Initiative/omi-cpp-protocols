// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/TradeFlags.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace otcmarkets::linkats::multicast::link::v4_3 {


// Trade flags bitmap.
struct TradeFlags {

    static constexpr auto name = "Trade Flags";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr TradeFlags()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TradeFlags(const std::uint8_t &value)
     : value{ value } {}

    // get value of TradeFlags field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
