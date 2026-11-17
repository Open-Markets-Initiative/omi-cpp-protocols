// Miax.MiaxOptions.ComplexTopOfMarket.Mach.v1.1: messages/Heartbeat.hpp
#pragma once

#include <cstdint>

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

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
