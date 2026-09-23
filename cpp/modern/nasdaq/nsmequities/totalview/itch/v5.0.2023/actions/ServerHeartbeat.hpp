#pragma once

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// Server Heartbeat
struct ServerHeartbeat {

    static constexpr auto name = "Server Heartbeat";

    // selected when ServerPacketType == 'H'
    static constexpr auto field = "ServerPacketType";
    static constexpr char value = 'H';

    // action properties
    static constexpr auto session = "Heartbeat";
    static constexpr auto origin = "Exchange";
};

}
