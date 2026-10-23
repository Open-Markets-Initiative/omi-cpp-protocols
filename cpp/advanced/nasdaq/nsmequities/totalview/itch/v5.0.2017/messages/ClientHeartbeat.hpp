#pragma once

namespace nasdaq::nsmequities::totalview::itch::v5_0_2017 {

// Client Heartbeat
struct client_heartbeat {

    static constexpr auto name = "Client Heartbeat";

    // selected when client_packet_type == 'R'
    static constexpr auto field = "client_packet_type";
    static constexpr char value = 'R';

    // action properties
    static constexpr auto session = "Heartbeat";
    static constexpr auto origin = "Client";
};

}
