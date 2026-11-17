// Miax.MiaxOptions.ComplexTopOfMarket.Mach.v1.1: actions/Heartbeat.hpp
#pragma once

#include <cstdint>

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

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
