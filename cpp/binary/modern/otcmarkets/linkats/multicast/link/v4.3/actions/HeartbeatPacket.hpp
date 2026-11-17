// OtcMarkets.LinkAts.Multicast.Link.v4.3: actions/HeartbeatPacket.hpp
#pragma once

namespace otcmarkets::linkats::multicast::link::v4_3 {

// Heartbeat Packet
struct HeartbeatPacket {

    static constexpr auto name = "Heartbeat Packet";

    // selected when Heartbeat == true
    static constexpr auto field = "Heartbeat";
    static constexpr bool value = true;

    // action properties
    static constexpr auto session = "Heartbeat";
    static constexpr auto origin = "Exchange";
};

}
