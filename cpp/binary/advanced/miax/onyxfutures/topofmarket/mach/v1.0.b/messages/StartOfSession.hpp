// Miax.OnyxFutures.TopOfMarket.Mach.v1.0.b: messages/StartOfSession.hpp
#pragma once

#include <cstdint>

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

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
