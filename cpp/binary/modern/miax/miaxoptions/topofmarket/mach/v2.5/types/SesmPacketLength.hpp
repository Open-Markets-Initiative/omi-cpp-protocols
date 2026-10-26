#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

// The length of rest of the packet
struct SesmPacketLength {

    static constexpr const char* name = "Sesm Packet Length";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr SesmPacketLength()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SesmPacketLength(const std::uint16_t value)
     : value{ value } {}

    // get value of SesmPacketLength field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
