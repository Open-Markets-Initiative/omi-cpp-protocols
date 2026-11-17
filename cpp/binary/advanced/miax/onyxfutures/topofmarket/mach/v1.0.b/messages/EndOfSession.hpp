// Miax.OnyxFutures.TopOfMarket.Mach.v1.0.b: messages/EndOfSession.hpp
#pragma once

#include <cstdint>

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

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
