#pragma once

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// Client Heartbeat
struct client_heartbeat {

    static constexpr auto name = "Client Heartbeat";

    // selected when esesm_packet_type == '1'
    static constexpr auto field = "esesm_packet_type";
    static constexpr char value = '1';
};

}
