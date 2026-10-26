#pragma once

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

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
