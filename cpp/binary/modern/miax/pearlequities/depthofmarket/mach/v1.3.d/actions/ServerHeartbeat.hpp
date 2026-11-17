// Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d: actions/ServerHeartbeat.hpp
#pragma once

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// Server Heartbeat
struct ServerHeartbeat {

    static constexpr auto name = "Server Heartbeat";

    // selected when EsesmPacketType == '0'
    static constexpr auto field = "EsesmPacketType";
    static constexpr char value = '0';

    // action properties
    static constexpr auto session = "Heartbeat";
    static constexpr auto origin = "Exchange";
};

}
