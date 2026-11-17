// Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d: messages/ServerHeartbeat.hpp
#pragma once

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// Server Heartbeat
struct server_heartbeat {

    static constexpr auto name = "Server Heartbeat";

    // selected when esesm_packet_type == '0'
    static constexpr auto field = "esesm_packet_type";
    static constexpr char value = '0';

    // action properties
    static constexpr auto session = "Heartbeat";
    static constexpr auto origin = "Exchange";
};

}
