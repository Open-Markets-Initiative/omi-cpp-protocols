// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/SecurityDetailSize.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace otcmarkets::linkats::multicast::link::v4_3 {


// Size of the SecurityDetail field. If zero, SecurityDetail is not present.
struct SecurityDetailSize {

    static constexpr auto name = "Security Detail Size";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr SecurityDetailSize()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SecurityDetailSize(const std::uint8_t &value)
     : value{ value } {}

    // get value of SecurityDetailSize field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
