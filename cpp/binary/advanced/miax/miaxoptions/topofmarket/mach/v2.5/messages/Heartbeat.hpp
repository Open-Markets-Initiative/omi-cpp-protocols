// Miax.MiaxOptions.TopOfMarket.Mach.v2.5: messages/Heartbeat.hpp
#pragma once

#include <cstdint>

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

// Heartbeat
struct heartbeat {

    static constexpr auto name = "Heartbeat";

    // selected when packet_type == 0
    static constexpr auto field = "packet_type";
    static constexpr std::uint8_t value = 0;

    // action properties
    static constexpr auto session = "Heartbeat";
    static constexpr auto origin = "Exchange";
};

}
