// Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d: actions/Heartbeat.hpp
#pragma once

#include <cstdint>

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// Heartbeat
struct Heartbeat {

    static constexpr auto name = "Heartbeat";

    // selected when MachPacketType == 0
    static constexpr auto field = "MachPacketType";
    static constexpr std::uint8_t value = 0;

    // action properties
    static constexpr auto session = "Heartbeat";
    static constexpr auto origin = "Exchange";
};

}
