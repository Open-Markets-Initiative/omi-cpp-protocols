#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// Length of the packet
struct MachPacketLength {

    static constexpr const char* name = "Mach Packet Length";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr MachPacketLength()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MachPacketLength(const std::uint16_t value)
     : value{ value } {}

    // get value of MachPacketLength field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
