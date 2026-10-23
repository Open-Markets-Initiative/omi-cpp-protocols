#pragma once

#include <cstdint>

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

// Start Of Session
struct start_of_session {

    static constexpr auto name = "Start Of Session";

    // selected when packet_type == 1
    static constexpr auto field = "packet_type";
    static constexpr std::uint8_t value = 1;
};

}
