#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {


// Mach packet type
struct MachPacketType {

    static constexpr auto name = "Mach Packet Type";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr MachPacketType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MachPacketType(const std::uint8_t &value)
     : value{ value } {}

    // get value of MachPacketType field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
