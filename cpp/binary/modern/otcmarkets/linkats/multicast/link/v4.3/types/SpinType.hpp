// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/SpinType.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace otcmarkets::linkats::multicast::link::v4_3 {


// Spin type
struct SpinType {

    static constexpr auto name = "Spin Type";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr SpinType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SpinType(const std::uint8_t &value)
     : value{ value } {}

    // get value of SpinType field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
