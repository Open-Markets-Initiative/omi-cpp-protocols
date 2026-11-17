// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/MessageSize.hpp
#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace otcmarkets::linkats::multicast::link::v4_3 {

// Size of message in bytes
struct MessageSize {

    static constexpr const char* name = "Message Size";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr MessageSize()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MessageSize(const std::uint16_t value)
     : value{ std::byteswap(value) } {}

    // get value of MessageSize field
    [[nodiscard]] std::uint16_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint16_t value;
};
}
