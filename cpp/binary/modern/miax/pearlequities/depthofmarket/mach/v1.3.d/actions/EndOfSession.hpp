// Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d: actions/EndOfSession.hpp
#pragma once

#include <cstdint>

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// End Of Session
struct EndOfSession {

    static constexpr auto name = "End Of Session";

    // selected when MachPacketType == 2
    static constexpr auto field = "MachPacketType";
    static constexpr std::uint8_t value = 2;

    // action properties
    static constexpr auto session = "End";
    static constexpr auto origin = "Exchange";
};

}
