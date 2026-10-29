#pragma once

namespace jnx::jnxequities::pts::itch::v1_7 {

// Server Heartbeat Packet
struct ServerHeartbeatPacket {

    static constexpr auto name = "Server Heartbeat Packet";

    // selected when ServerPacketType == 'H'
    static constexpr auto field = "ServerPacketType";
    static constexpr char value = 'H';

    // action properties
    static constexpr auto session = "Heartbeat";
    static constexpr auto origin = "Exchange";
};

}
