#pragma once

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// Server Heartbeat
struct server_heartbeat {

    static constexpr auto name = "Server Heartbeat";

    // selected when esesm_packet_type == '0'
    static constexpr auto field = "esesm_packet_type";
    static constexpr char value = '0';
};

}
