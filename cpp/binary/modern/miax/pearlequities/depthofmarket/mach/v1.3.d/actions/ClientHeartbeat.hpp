// Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d: actions/ClientHeartbeat.hpp
#pragma once

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// Client Heartbeat
struct ClientHeartbeat {

    static constexpr auto name = "Client Heartbeat";

    // selected when EsesmPacketType == '1'
    static constexpr auto field = "EsesmPacketType";
    static constexpr char value = '1';

    // action properties
    static constexpr auto session = "Heartbeat";
    static constexpr auto origin = "Client";
};

}
