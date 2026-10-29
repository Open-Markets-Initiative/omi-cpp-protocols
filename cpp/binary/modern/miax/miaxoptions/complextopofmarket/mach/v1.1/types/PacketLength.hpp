#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

// Length of the packet, including the header and application data
struct PacketLength {

    static constexpr const char* name = "Packet Length";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr PacketLength()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PacketLength(const std::uint16_t value)
     : value{ value } {}

    // get value of PacketLength field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
