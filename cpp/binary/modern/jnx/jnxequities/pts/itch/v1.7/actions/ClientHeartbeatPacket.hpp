#pragma once

namespace jnx::jnxequities::pts::itch::v1_7 {

// Client Heartbeat Packet
struct ClientHeartbeatPacket {

    static constexpr auto name = "Client Heartbeat Packet";

    // selected when ClientPacketType == 'R'
    static constexpr auto field = "ClientPacketType";
    static constexpr char value = 'R';

    // action properties
    static constexpr auto session = "Heartbeat";
    static constexpr auto origin = "Client";
};

}
