// Miax.MiaxOptions.ComplexTopOfMarket.Mach.v1.1: messages/EndOfSession.hpp
#pragma once

#include <cstdint>

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

// End Of Session
struct end_of_session {

    static constexpr auto name = "End Of Session";

    // selected when packet_type == 2
    static constexpr auto field = "packet_type";
    static constexpr std::uint8_t value = 2;

    // action properties
    static constexpr auto session = "End";
    static constexpr auto origin = "Exchange";
};

}
