#pragma once

#include <cstddef>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {


// Code identifying this packet type sent by the client
struct ClientPacketType {

    static constexpr auto name = "Client Packet Type";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr ClientPacketType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ClientPacketType(const char &value)
     : value{ value } {}

    // get value of ClientPacketType field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
