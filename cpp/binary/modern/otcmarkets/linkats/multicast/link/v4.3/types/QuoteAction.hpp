// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/QuoteAction.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace otcmarkets::linkats::multicast::link::v4_3 {


// Quote action indicator.
struct QuoteAction {

    static constexpr auto name = "Quote Action";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr QuoteAction()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit QuoteAction(const std::uint8_t &value)
     : value{ value } {}

    // get value of QuoteAction field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
