#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v2_1 {


// Packet Reserved Field
struct PacketReserved {

    static constexpr auto name = "Packet Reserved";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr PacketReserved()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PacketReserved(const std::uint8_t &value)
     : value{ value } {}

    // get value of PacketReserved field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
