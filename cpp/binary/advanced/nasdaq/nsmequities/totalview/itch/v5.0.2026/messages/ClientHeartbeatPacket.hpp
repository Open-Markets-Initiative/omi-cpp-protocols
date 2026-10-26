#pragma once

namespace nasdaq::nsmequities::totalview::itch::v5_0_2026 {

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
