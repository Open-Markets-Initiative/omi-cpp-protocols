#pragma once

namespace jnx::jnxequities::pts::itch::v1_7 {

// Logout Request Packet
struct LogoutRequestPacket {

    static constexpr auto name = "Logout Request Packet";

    // selected when ClientPacketType == 'O'
    static constexpr auto field = "ClientPacketType";
    static constexpr char value = 'O';

    // action properties
    static constexpr auto session = "Logout";
    static constexpr auto origin = "Client";
};

}
