// Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d: actions/StartOfSession.hpp
#pragma once

#include <cstdint>

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// Start Of Session
struct StartOfSession {

    static constexpr auto name = "Start Of Session";

    // selected when MachPacketType == 1
    static constexpr auto field = "MachPacketType";
    static constexpr std::uint8_t value = 1;

    // action properties
    static constexpr auto session = "Start";
    static constexpr auto origin = "Exchange";
};

}
