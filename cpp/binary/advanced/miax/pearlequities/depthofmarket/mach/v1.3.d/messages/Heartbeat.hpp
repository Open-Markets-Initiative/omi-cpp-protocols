// Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d: messages/Heartbeat.hpp
#pragma once

#include <cstdint>

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// Heartbeat
struct heartbeat {

    static constexpr auto name = "Heartbeat";

    // selected when mach_packet_type == 0
    static constexpr auto field = "mach_packet_type";
    static constexpr std::uint8_t value = 0;

    // action properties
    static constexpr auto session = "Heartbeat";
    static constexpr auto origin = "Exchange";
};

}
