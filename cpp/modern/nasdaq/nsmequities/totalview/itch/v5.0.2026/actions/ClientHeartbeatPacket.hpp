#pragma once

namespace nasdaq::nsmequities::totalview::itch::v5_0_2026 {

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
