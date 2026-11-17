// OtcMarkets.LinkAts.Multicast.Link.v4.3: messages/HeartbeatPacket.hpp
#pragma once

namespace otcmarkets::linkats::multicast::link::v4_3 {

// Heartbeat Packet
struct heartbeat_packet {

    static constexpr auto name = "Heartbeat Packet";

    // selected when heartbeat == true
    static constexpr auto field = "heartbeat";
    static constexpr bool value = true;

    // action properties
    static constexpr auto session = "Heartbeat";
    static constexpr auto origin = "Exchange";
};

}
