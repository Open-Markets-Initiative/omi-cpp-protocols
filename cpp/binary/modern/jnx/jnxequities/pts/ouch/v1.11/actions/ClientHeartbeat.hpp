#pragma once

namespace jnx::jnxequities::pts::ouch::v1_11 {

// Client Heartbeat
struct ClientHeartbeat {

    static constexpr auto name = "Client Heartbeat";

    // selected when ClientPacketType == 'R'
    static constexpr auto field = "ClientPacketType";
    static constexpr char value = 'R';

    // action properties
    static constexpr auto session = "Heartbeat";
    static constexpr auto origin = "Client";
};

}
