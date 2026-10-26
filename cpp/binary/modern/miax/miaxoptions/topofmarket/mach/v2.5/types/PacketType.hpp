#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::miaxoptions::topofmarket::mach::v2_5 {


// protocol packet type
struct PacketType {

    static constexpr auto name = "Packet Type";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr PacketType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PacketType(const std::uint8_t &value)
     : value{ value } {}

    // get value of PacketType field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
