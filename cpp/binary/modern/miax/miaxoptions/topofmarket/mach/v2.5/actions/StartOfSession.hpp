// Miax.MiaxOptions.TopOfMarket.Mach.v2.5: actions/StartOfSession.hpp
#pragma once

#include <cstdint>

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

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
