// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/InsideAction.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace otcmarkets::linkats::multicast::link::v4_3 {


// Inside action indicator.
struct InsideAction {

    static constexpr auto name = "Inside Action";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr InsideAction()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit InsideAction(const std::uint8_t &value)
     : value{ value } {}

    // get value of InsideAction field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
