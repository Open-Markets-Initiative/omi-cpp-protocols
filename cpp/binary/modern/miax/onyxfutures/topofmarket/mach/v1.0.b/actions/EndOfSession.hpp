// Miax.OnyxFutures.TopOfMarket.Mach.v1.0.b: actions/EndOfSession.hpp
#pragma once

#include <cstdint>

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

// End Of Session
struct EndOfSession {

    static constexpr auto name = "End Of Session";

    // selected when PacketType == 2
    static constexpr auto field = "PacketType";
    static constexpr std::uint8_t value = 2;

    // action properties
    static constexpr auto session = "End";
    static constexpr auto origin = "Exchange";
};

}
