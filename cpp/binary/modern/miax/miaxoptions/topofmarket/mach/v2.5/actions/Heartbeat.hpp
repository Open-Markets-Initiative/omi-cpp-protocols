// Miax.MiaxOptions.TopOfMarket.Mach.v2.5: actions/Heartbeat.hpp
#pragma once

#include <cstdint>

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

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
