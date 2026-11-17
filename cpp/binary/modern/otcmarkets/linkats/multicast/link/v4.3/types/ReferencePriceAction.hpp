// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/ReferencePriceAction.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace otcmarkets::linkats::multicast::link::v4_3 {


// Reference price action indicator.
struct ReferencePriceAction {

    static constexpr auto name = "Reference Price Action";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr ReferencePriceAction()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ReferencePriceAction(const std::uint8_t &value)
     : value{ value } {}

    // get value of ReferencePriceAction field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
