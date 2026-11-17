// Miax.OnyxFutures.TopOfMarket.Mach.v1.0.b: actions/Heartbeat.hpp
#pragma once

#include <cstdint>

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

// Heartbeat
struct Heartbeat {

    static constexpr auto name = "Heartbeat";

    // selected when PacketType == 0
    static constexpr auto field = "PacketType";
    static constexpr std::uint8_t value = 0;

    // action properties
    static constexpr auto session = "Heartbeat";
    static constexpr auto origin = "Exchange";
};

}
