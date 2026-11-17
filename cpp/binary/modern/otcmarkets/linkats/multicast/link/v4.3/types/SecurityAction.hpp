// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/SecurityAction.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace otcmarkets::linkats::multicast::link::v4_3 {


// Security action indicator.
struct SecurityAction {

    static constexpr auto name = "Security Action";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr SecurityAction()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SecurityAction(const std::uint8_t &value)
     : value{ value } {}

    // get value of SecurityAction field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
