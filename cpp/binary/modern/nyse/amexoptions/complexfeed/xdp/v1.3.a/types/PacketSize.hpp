#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {

// The size of the packet in bytes, including this 16 byte packet header
struct PacketSize {

    static constexpr const char* name = "Packet Size";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr PacketSize()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PacketSize(const std::uint16_t value)
     : value{ value } {}

    // get value of PacketSize field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
