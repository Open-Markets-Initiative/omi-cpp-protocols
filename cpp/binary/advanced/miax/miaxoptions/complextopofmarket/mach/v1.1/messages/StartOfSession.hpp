// Miax.MiaxOptions.ComplexTopOfMarket.Mach.v1.1: messages/StartOfSession.hpp
#pragma once

#include <cstdint>

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

// Start Of Session
struct start_of_session {

    static constexpr auto name = "Start Of Session";

    // selected when packet_type == 1
    static constexpr auto field = "packet_type";
    static constexpr std::uint8_t value = 1;

    // action properties
    static constexpr auto session = "Start";
    static constexpr auto origin = "Exchange";
};

}
