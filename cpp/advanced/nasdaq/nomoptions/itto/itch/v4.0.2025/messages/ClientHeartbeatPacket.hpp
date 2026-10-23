#pragma once

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

// Client Heartbeat Packet
struct client_heartbeat_packet {

    static constexpr auto name = "Client Heartbeat Packet";

    // selected when client_packet_type == 'R'
    static constexpr auto field = "client_packet_type";
    static constexpr char value = 'R';

    // action properties
    static constexpr auto session = "Heartbeat";
    static constexpr auto origin = "Client";
};

}
