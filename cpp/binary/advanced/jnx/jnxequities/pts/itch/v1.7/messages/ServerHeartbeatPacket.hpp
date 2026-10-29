#pragma once

namespace jnx::jnxequities::pts::itch::v1_7 {

// Server Heartbeat Packet
struct server_heartbeat_packet {

    static constexpr auto name = "Server Heartbeat Packet";

    // selected when server_packet_type == 'H'
    static constexpr auto field = "server_packet_type";
    static constexpr char value = 'H';

    // action properties
    static constexpr auto session = "Heartbeat";
    static constexpr auto origin = "Exchange";
};

}
