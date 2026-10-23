#pragma once

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

// Client Heartbeat
struct client_heartbeat {

    static constexpr auto name = "Client Heartbeat";

    // selected when sesm_packet_type == '1'
    static constexpr auto field = "sesm_packet_type";
    static constexpr char value = '1';
};

}
