// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/AskNumPricedMp.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace otcmarkets::linkats::multicast::link::v4_3 {


// Number of market participants at the inside ask price level.
struct AskNumPricedMp {

    static constexpr auto name = "Ask Num Priced Mp";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr AskNumPricedMp()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit AskNumPricedMp(const std::uint8_t &value)
     : value{ value } {}

    // get value of AskNumPricedMp field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
