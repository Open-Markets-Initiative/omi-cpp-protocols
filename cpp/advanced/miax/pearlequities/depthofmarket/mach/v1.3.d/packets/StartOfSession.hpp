#pragma once

#include <cstdint>

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// Start Of Session
struct start_of_session {

    static constexpr auto name = "Start Of Session";

    // selected when mach_packet_type == 1
    static constexpr auto field = "mach_packet_type";
    static constexpr std::uint8_t value = 1;
};

}
