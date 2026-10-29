#pragma once

#include <cstddef>

namespace jnx::jnxequities::pts::itch::v1_7 {


// Code identifying this packet type sent by the server
struct ServerPacketType {

    static constexpr auto name = "Server Packet Type";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr ServerPacketType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ServerPacketType(const char &value)
     : value{ value } {}

    // get value of ServerPacketType field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
