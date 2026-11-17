// Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d: messages/ClientHeartbeat.hpp
#pragma once

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// Client Heartbeat
struct client_heartbeat {

    static constexpr auto name = "Client Heartbeat";

    // selected when esesm_packet_type == '1'
    static constexpr auto field = "esesm_packet_type";
    static constexpr char value = '1';

    // action properties
    static constexpr auto session = "Heartbeat";
    static constexpr auto origin = "Client";
};

}
