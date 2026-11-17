// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/Tier.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace otcmarkets::linkats::multicast::link::v4_3 {


// The market tier assigned by OTC Markets Group.
struct Tier {

    static constexpr auto name = "Tier";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr Tier()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Tier(const std::uint8_t &value)
     : value{ value } {}

    // get value of Tier field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
