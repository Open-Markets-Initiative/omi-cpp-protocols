// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/TradeAction.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace otcmarkets::linkats::multicast::link::v4_3 {


// Trade action indicator.
struct TradeAction {

    static constexpr auto name = "Trade Action";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr TradeAction()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TradeAction(const std::uint8_t &value)
     : value{ value } {}

    // get value of TradeAction field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
