// Miax.MiaxOptions.TopOfMarket.Mach.v2.5: actions/EndOfSession.hpp
#pragma once

#include <cstdint>

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

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
