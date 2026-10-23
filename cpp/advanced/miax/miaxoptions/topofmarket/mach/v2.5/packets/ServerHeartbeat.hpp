#pragma once

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

// Server Heartbeat
struct server_heartbeat {

    static constexpr auto name = "Server Heartbeat";

    // selected when sesm_packet_type == '0'
    static constexpr auto field = "sesm_packet_type";
    static constexpr char value = '0';
};

}
