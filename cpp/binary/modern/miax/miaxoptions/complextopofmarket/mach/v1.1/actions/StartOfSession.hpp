// Miax.MiaxOptions.ComplexTopOfMarket.Mach.v1.1: actions/StartOfSession.hpp
#pragma once

#include <cstdint>

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

// Start Of Session
struct StartOfSession {

    static constexpr auto name = "Start Of Session";

    // selected when PacketType == 1
    static constexpr auto field = "PacketType";
    static constexpr std::uint8_t value = 1;

    // action properties
    static constexpr auto session = "Start";
    static constexpr auto origin = "Exchange";
};

}
