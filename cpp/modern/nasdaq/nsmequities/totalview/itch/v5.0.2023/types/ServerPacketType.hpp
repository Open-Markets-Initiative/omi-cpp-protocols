#pragma once

#include <cstddef>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {


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
