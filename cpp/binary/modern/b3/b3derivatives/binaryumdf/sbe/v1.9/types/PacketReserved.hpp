// B3.B3Derivatives.BinaryUmdf.Sbe.v1.9: types/PacketReserved.hpp
#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v1_9 {


// Reserved byte, carrying no meaning, between the channel id and the sequence version
struct PacketReserved {

    static constexpr auto name = "Packet Reserved";
    static constexpr std::size_t size = 1;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr PacketReserved()
     : value{} {}

  protected:
    type value;
};
}
