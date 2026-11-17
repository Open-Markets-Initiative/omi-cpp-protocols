// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/NumPricedMp.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace otcmarkets::linkats::multicast::link::v4_3 {


// Number of market participants at the inside price level.
struct NumPricedMp {

    static constexpr auto name = "Num Priced Mp";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr NumPricedMp()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit NumPricedMp(const std::uint8_t &value)
     : value{ value } {}

    // get value of NumPricedMp field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
