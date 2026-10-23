#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// The length of rest of the packet
struct EsesmPacketLength {

    static constexpr const char* name = "Esesm Packet Length";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr EsesmPacketLength()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit EsesmPacketLength(const std::uint16_t value)
     : value{ value } {}

    // get value of EsesmPacketLength field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
