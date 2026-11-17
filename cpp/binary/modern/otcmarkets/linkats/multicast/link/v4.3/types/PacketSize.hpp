// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/PacketSize.hpp
#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace otcmarkets::linkats::multicast::link::v4_3 {

// Size of packet in bytes
struct PacketSize {

    static constexpr const char* name = "Packet Size";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr PacketSize()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PacketSize(const std::uint16_t value)
     : value{ std::byteswap(value) } {}

    // get value of PacketSize field
    [[nodiscard]] std::uint16_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint16_t value;
};
}
